"""Upload Markdown statements, static testcases and editorials via problem-import."""

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

    def testcases(self, path, archive, manifest):
        boundary = 'problem-import-' + uuid.uuid4().hex
        # Stream the multipart body from disk rather than loading a large ZIP in RAM.
        with TemporaryFile() as body:
            body.write(('--' + boundary + '\r\nContent-Disposition: form-data; '
                        'name="manifest"\r\n\r\n').encode('ascii'))
            body.write(json.dumps(manifest, ensure_ascii=False).encode('utf-8'))
            body.write(('\r\n--' + boundary + '\r\nContent-Disposition: form-data; '
                        'name="upload"; filename="testcases.zip"\r\n'
                        'Content-Type: application/zip\r\n\r\n').encode('ascii'))
            with archive.open('rb') as source:
                shutil.copyfileobj(source, body)
            body.write(('\r\n--' + boundary + '--\r\n').encode('ascii'))
            length = body.tell()
            body.seek(0)
            self.request('POST', path, body, 'multipart/form-data; boundary=' + boundary,
                         200, length=length)


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
    def __init__(self, problem):
        self.problem = problem
        config = problem.config
        settings = config.get('upload', {})
        if not isinstance(settings, dict):
            raise UploadError('info.toml: [upload] must be a table')
        unknown = set(settings) - PROBLEM_FIELDS - {'editorial', 'manifest', 'checker'}
        if unknown:
            raise UploadError('Unknown [upload] fields: ' + ', '.join(sorted(unknown)))
        self.code = problem.basedir.name.lower()
        if not isinstance(self.code, str) or not re.fullmatch(r'[a-z0-9]{1,20}', self.code):
            raise UploadError('The problem directory name must contain 1-20 letters or digits')
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
            if checker not in CHECKERS:
                raise UploadError('Unsupported API checker: {}'.format(checker))
            self.manifest = {'checker': checker, 'cases': [
                {'input_file': name + '.in', 'output_file': name + '.out'}
                for name in self.cases
            ]}

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
            logger.info('Upload statement: %s', self.code)
            try:
                client.json('POST', '/problems', dict(self.payload, code=self.code), 201)
            except UploadError as exc:
                if exc.status != 409:
                    raise
                client.json('PATCH', path, self.payload, 200)
            logger.info('Upload %d testcases: %s', len(self.cases), self.code)
            client.testcases(path + '/testcases', archive, self.manifest)
            if self.editorial is not None:
                logger.info('Upload editorial: %s', self.code)
                client.json('PUT', path + '/editorial', {'content': self.editorial}, 200)
            logger.info('Upload complete: %s', self.code)
