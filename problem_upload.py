"""Upload statements, checkers, static testcases and editorials via problem-import."""

import json
import os
import re
import shutil
import uuid
import zipfile
from logging import getLogger
from pathlib import Path
from tempfile import TemporaryDirectory, TemporaryFile
from urllib.error import HTTPError, URLError
from urllib.parse import urlsplit, urlunsplit
from urllib.request import HTTPRedirectHandler, Request, build_opener

from problem import casename


logger = getLogger(__name__)
API_PATH = '/api/v3/problem-import'
PROBLEM_FIELDS = {
    'group', 'classes', 'types', 'allowed_languages', 'time_limit',
    'memory_limit', 'points', 'partial', 'short_circuit', 'is_public', 'summary',
}
CHECKERS = {'standard', 'floats', 'floatsabs', 'floatsrel', 'rstripped',
            'sorted', 'identical', 'linecount'}
CUSTOM_CHECKERS = {'custom', 'bridged'}
MAX_CHECKER_BYTES = 1024 * 1024


class UploadError(RuntimeError):
    def __init__(self, message, status=None):
        super().__init__(message)
        self.status = status


class NoRedirect(HTTPRedirectHandler):
    def redirect_request(self, req, fp, code, msg, headers, newurl):
        # Never forward the API key to a redirect destination.
        return None


class UploadClient:
    def __init__(self, host, api_key):
        if not host or not host.strip():
            raise UploadError('Set HOST to the server URL (for example https://judge.example.com)')
        if not api_key or not api_key.strip():
            raise UploadError('Set PROBLEM_IMPORT_API_KEY before using --upload')
        if any(c in api_key for c in '\r\n'):
            raise UploadError('PROBLEM_IMPORT_API_KEY contains invalid characters')
        host = host.strip()
        if '://' not in host:
            host = 'https://' + host
        parsed = urlsplit(host)
        if (parsed.scheme not in ('http', 'https') or not parsed.hostname
                or parsed.username or parsed.password or parsed.query or parsed.fragment
                or parsed.path.rstrip('/') not in ('', API_PATH)):
            raise UploadError('HOST must be an HTTP(S) server URL or problem-import API URL')
        self.base_url = urlunsplit((parsed.scheme, parsed.netloc, API_PATH, '', ''))
        self.api_key = api_key.strip()
        self.opener = build_opener(NoRedirect())

    @classmethod
    def from_env(cls):
        return cls(os.getenv('HOST'), os.getenv('PROBLEM_IMPORT_API_KEY'))

    def request(self, method, path, data, content_type, expected_status, length=None):
        headers = {'Authorization': 'Bearer ' + self.api_key,
                   'Content-Type': content_type, 'Accept': 'application/json'}
        if length is not None:
            headers['Content-Length'] = str(length)
        request = Request(self.base_url + path, data=data, headers=headers, method=method)
        try:
            with self.opener.open(request, timeout=120) as response:
                if response.status != expected_status:
                    raise UploadError('{} {}: unexpected HTTP {}'.format(
                        method, path, response.status), response.status)
        except HTTPError as exc:
            with exc:
                detail = exc.read(8192).decode('utf-8', errors='replace')
            detail = detail.replace(self.api_key, '[REDACTED]')
            raise UploadError('{} {}: HTTP {} {}'.format(
                method, path, exc.code, detail), exc.code) from None
        except (URLError, OSError) as exc:
            detail = str(exc).replace(self.api_key, '[REDACTED]')
            raise UploadError('{} {}: {}'.format(method, path, detail)) from None

    def json(self, method, path, payload, expected_status):
        data = json.dumps(payload, ensure_ascii=False).encode('utf-8')
        self.request(method, path, data, 'application/json', expected_status)

    def multipart(self, path, fields, files):
        boundary = 'problem-import-' + uuid.uuid4().hex
        # Stream the multipart body from disk rather than loading a large ZIP in RAM.
        with TemporaryFile() as body:
            for name, value in fields.items():
                body.write(('--' + boundary + '\r\nContent-Disposition: form-data; '
                            'name="' + name + '"\r\n\r\n').encode('ascii'))
                body.write(value.encode('utf-8'))
                body.write(b'\r\n')
            for name, filename, content_type, data in files:
                body.write(('--' + boundary + '\r\nContent-Disposition: form-data; '
                            'name="' + name + '"; filename="' + filename + '"\r\n'
                            'Content-Type: ' + content_type + '\r\n\r\n').encode('ascii'))
                if isinstance(data, Path):
                    with data.open('rb') as source:
                        shutil.copyfileobj(source, body)
                else:
                    body.write(data)
                body.write(b'\r\n')
            body.write(('--' + boundary + '--\r\n').encode('ascii'))
            length = body.tell()
            body.seek(0)
            self.request('POST', path, body, 'multipart/form-data; boundary=' + boundary,
                         200, length=length)

    def testcases(self, path, archive, manifest):
        self.multipart(path, {'manifest': json.dumps(manifest, ensure_ascii=False)},
                       [('upload', 'testcases.zip', 'application/zip', archive)])

    def checker(self, path, filename, source, checker_args):
        self.multipart(path, {'checker_args': json.dumps(checker_args, ensure_ascii=False,
                                                        allow_nan=False)},
                       [('upload', filename, 'text/plain; charset=utf-8', source)])


def read_checker_source(path):
    if path.suffix.lower() not in ('.cpp', '.py'):
        raise UploadError('Custom checker must be a .cpp or .py source file: {}'.format(path))
    try:
        with path.open('rb') as source:
            content = source.read(MAX_CHECKER_BYTES + 1)
    except OSError as exc:
        raise UploadError('Cannot read custom checker {}: {}'.format(path, exc)) from None
    if len(content) > MAX_CHECKER_BYTES:
        raise UploadError('Custom checker exceeds the 1 MiB limit: {}'.format(path))
    try:
        text = content.decode('utf-8')
    except UnicodeDecodeError:
        raise UploadError('Custom checker must be UTF-8: {}'.format(path)) from None
    if not text.strip():
        raise UploadError('Custom checker is empty: {}'.format(path))
    if '\0' in text:
        raise UploadError('Custom checker contains a NUL byte: {}'.format(path))
    return content


def validate_checker_args(value):
    if not isinstance(value, dict):
        raise UploadError('checker_args must be a JSON object')
    try:
        json.dumps(value, allow_nan=False)
    except (TypeError, ValueError):
        raise UploadError('checker_args must be a valid JSON object') from None
    return value


def read_markdown(path):
    content = path.read_text(encoding='utf-8')
    if not content.strip():
        raise UploadError('{} is empty'.format(path))
    return content


def statement_parts(content):
    fence = None
    lines = content.splitlines(keepends=True)
    for index, raw_line in enumerate(lines):
        line = raw_line.rstrip('\r\n')
        marker = re.match(r'^ {0,3}(`{3,}|~{3,})', line)
        if marker:
            delimiter = marker.group(1)
            if fence is None:
                fence = delimiter
            elif delimiter[0] == fence[0] and len(delimiter) >= len(fence):
                fence = None
            continue
        if fence is None:
            heading = re.match(r'^ {0,3}#[ \t]+(.+?)(?:[ \t]+#+)?[ \t]*$', line)
            if heading and heading.group(1).strip():
                return heading.group(1).strip(), ''.join(lines[:index] + lines[index + 1:])
    return None, content


class ProblemUpload:
    def __init__(self, problem, skip_statement=False):
        self.problem = problem
        self.skip_statement = skip_statement
        config = problem.config
        settings = config.get('upload', {})
        if not isinstance(settings, dict):
            raise UploadError('info.toml: [upload] must be a table')
        unknown = set(settings) - PROBLEM_FIELDS - {
            'editorial', 'manifest', 'checker', 'custom_checker', 'checker_args',
        }
        if unknown:
            raise UploadError('Unknown [upload] fields: ' + ', '.join(sorted(unknown)))
        self.code = problem.basedir.name.lower()
        if not isinstance(self.code, str) or not re.fullmatch(r'[a-z0-9]{1,20}', self.code):
            raise UploadError('The problem directory name must contain 1-20 letters or digits')
        self.payload = {}
        if not skip_statement:
            self.payload = {key: value for key, value in settings.items() if key in PROBLEM_FIELDS}
            self.payload.setdefault('time_limit', config.get('timelimit'))
            name, description = statement_parts(read_markdown(problem.basedir / 'task.md'))
            if not description.strip():
                raise UploadError('task.md must contain statement content besides its heading')
            self.payload['description'] = description
            self.payload['name'] = name if name is not None else config.get('title')
            if not isinstance(self.payload['name'], str) or not self.payload['name'].strip():
                raise UploadError('Add a # heading to task.md or set title in info.toml')
            for field in ('group', 'classes'):
                if not isinstance(self.payload.get(field), str) or not self.payload[field].strip():
                    raise UploadError('Set [upload].{} in {}'.format(field, problem.basedir / 'info.toml'))
            for field in ('types', 'allowed_languages'):
                value = self.payload.get(field)
                if (not isinstance(value, list) or not value
                        or any(not isinstance(item, str) or not item.strip() for item in value)):
                    raise UploadError('Set [upload].{} to a non-empty list of strings'.format(field))
            if any(value is None for value in self.payload.values()):
                raise UploadError('Upload metadata must not contain null values; set timelimit or [upload].time_limit')

        self.editorial = None
        if 'editorial' in settings:
            self.editorial = read_markdown(problem.basedir / settings['editorial'])
        else:
            for name in ('editorial.md', 'solution.md'):
                path = problem.basedir / name
                if path.is_file():
                    self.editorial = read_markdown(path)
                    break

        self.cases = []
        for test in config['tests']:
            for index in range(test['number']):
                name = casename(test['name'], index)
                self.cases.append(name)
        if not self.cases or len(set(self.cases)) != len(self.cases):
            raise UploadError('Upload requires at least one testcase and unique testcase names')
        if 'manifest' in settings:
            with (problem.basedir / settings['manifest']).open(encoding='utf-8') as source:
                self.manifest = json.load(source)
            if not isinstance(self.manifest, dict):
                raise UploadError('The testcase manifest must be a JSON object')
        else:
            checker = settings.get('checker', 'standard')
            self.manifest = {'checker': checker, 'cases': [
                {'input_file': name + '.in', 'output_file': name + '.out'}
                for name in self.cases
            ]}

        checker = self.manifest.get('checker', settings.get('checker', 'standard'))
        configured_checker = settings.get('checker')
        if configured_checker is not None and not isinstance(configured_checker, str):
            raise UploadError('[upload].checker must be a checker name')
        source = settings.get('custom_checker')
        if source is not None and (not isinstance(source, str) or not source.strip()):
            raise UploadError('[upload].custom_checker must be a source file path')
        if not isinstance(checker, str) or checker not in CHECKERS | CUSTOM_CHECKERS:
            raise UploadError('Unsupported API checker: {}'.format(checker))
        custom = (source is not None or checker in CUSTOM_CHECKERS
                  or configured_checker in CUSTOM_CHECKERS)
        self.custom_checker = None
        self.checker_source = None
        self.checker_args = validate_checker_args(
            self.manifest.get('checker_args', settings.get('checker_args', {})))
        if custom:
            # A source file must never be uploaded and then replaced by a built-in checker.
            if ((configured_checker is not None and configured_checker not in CUSTOM_CHECKERS)
                    or ('manifest' in settings and 'checker' in self.manifest
                        and checker not in CUSTOM_CHECKERS)):
                raise UploadError('Custom checker source conflicts with a built-in checker setting')
            self.custom_checker = problem.basedir / source if source is not None else problem.checker
            self.checker_source = read_checker_source(self.custom_checker)
            # /checker chooses the correct server-side filename and configuration for C++/Python.
            # The following ZIP import must preserve that configuration, including its files/args.
            self.manifest.pop('checker', None)
            self.manifest.pop('checker_args', None)
        elif 'checker_args' in settings:
            self.manifest.setdefault('checker_args', self.checker_args)

    def upload(self, client):
        problem = self.problem
        problem.assert_hashes()
        with TemporaryDirectory() as directory:
            archive = Path(directory) / 'testcases.zip'
            with zipfile.ZipFile(str(archive), 'w', zipfile.ZIP_DEFLATED) as output:
                for name in self.cases:
                    for folder, extension in (('in', '.in'), ('out', '.out')):
                        source = problem.basedir / folder / (name + extension)
                        if not source.is_file():
                            raise UploadError('Missing testcase file: {}'.format(source))
                        output.write(str(source), name + extension)
            # Finish reading/packing all local files before mutating the server.
            path = '/problems/' + self.code
            if self.skip_statement:
                logger.info('Skip statement and metadata: %s', self.code)
            else:
                logger.info('Upload statement: %s', self.code)
                try:
                    client.json('POST', '/problems', dict(self.payload, code=self.code), 201)
                except UploadError as exc:
                    if exc.status != 409:
                        raise
                    client.json('PATCH', path, self.payload, 200)
            if self.custom_checker is not None:
                logger.info('Upload checker: %s (%s)', self.code, self.custom_checker.name)
                filename = 'checker' + self.custom_checker.suffix.lower()
                client.checker(path + '/checker', filename, self.checker_source, self.checker_args)
            logger.info('Upload %d testcases: %s', len(self.cases), self.code)
            client.testcases(path + '/testcases', archive, self.manifest)
            if self.editorial is not None:
                logger.info('Upload editorial: %s', self.code)
                client.json('PUT', path + '/editorial', {'content': self.editorial}, 200)
            logger.info('Upload complete: %s', self.code)
