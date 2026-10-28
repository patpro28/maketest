#!/usr/bin/env python3

import io
import json
import os
import subprocess
import sys
import threading
import unittest
import zipfile
from email import policy
from email.parser import BytesParser
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
from tempfile import TemporaryDirectory
from unittest.mock import patch

import generate
from problem import Problem
from problem_upload import MAX_CHECKER_BYTES, ProblemUpload, UploadClient, UploadError


class ProblemUploadTests(unittest.TestCase):
    def setUp(self):
        self.temp = TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.directory = self.root / 'DEMO001'
        self.directory.mkdir()
        self.statement = '# Tính tổng hai số\n\n### Đề bài\nTính $a+b$.\n'
        (self.directory / 'task.md').write_text(self.statement, encoding='utf-8')
        (self.directory / 'info.toml').write_text('''title = 'Ignored TOML title'
timelimit = 2.0
[[tests]]
name = 'example.in'
number = 2
[upload]
group = 'basic'
classes = 'beginner'
types = ['implementation']
allowed_languages = ['PY3', 'CPP17']
memory_limit = 65536
''', encoding='utf-8')
        for folder in ('in', 'out', 'gen', 'sol'):
            (self.directory / folder).mkdir()
        for index, (a, b) in enumerate(((1, 2), (-4, 7))):
            name = 'example_{:02d}'.format(index)
            data = '{} {}\n'.format(a, b)
            (self.directory / 'in' / (name + '.in')).write_text(data)
            (self.directory / 'gen' / (name + '.in')).write_text(data)
            (self.directory / 'out' / (name + '.out')).write_text('{}\n'.format(a + b))
        (self.directory / 'sol' / 'correct.py').write_text(
            'import sys\nprint(sum(map(int, sys.stdin.read().split())))\n')
        # Use a Python reference solution for an actual CLI generation smoke test.
        with (self.directory / 'info.toml').open('a') as file:
            file.write("\n[[solutions]]\ntype = 'correct'\nname = 'correct.py'\n")
        self.problem = Problem(self.root, self.directory)
        (self.directory / 'hash.json').write_text(json.dumps(self.problem.calc_hashes()))
        self.requests = []
        self.statuses = []
        self.error_body = b'{"detail":"test error"}'
        owner = self

        class Handler(BaseHTTPRequestHandler):
            def do_POST(self):
                self.handle_request()

            do_PATCH = do_POST
            do_PUT = do_POST

            def handle_request(self):
                body = self.rfile.read(int(self.headers.get('Content-Length', 0)))
                owner.requests.append((self.command, self.path, self.headers, body))
                status = owner.statuses.pop(0) if owner.statuses else (
                    201 if self.path.endswith('/problems') else 200)
                self.send_response(status)
                if status in (301, 302, 307, 308):
                    self.send_header('Location', '/redirect-target')
                self.end_headers()
                self.wfile.write(owner.error_body if status >= 400 else b'{}')

            def log_message(self, *args):
                pass

        self.server = HTTPServer(('127.0.0.1', 0), Handler)
        self.thread = threading.Thread(target=self.server.serve_forever, daemon=True)
        self.thread.start()
        self.addCleanup(self.stop_server)
        self.host = 'http://127.0.0.1:{}'.format(self.server.server_port)
        self.client = UploadClient(self.host, 'test-api-key')

    def stop_server(self):
        self.server.shutdown()
        self.server.server_close()
        self.thread.join()

    def multipart(self, request):
        content_type = request[2]['Content-Type']
        message = BytesParser(policy=policy.default).parsebytes(
            ('Content-Type: ' + content_type + '\r\nMIME-Version: 1.0\r\n\r\n').encode()
            + request[3])
        return {part.get_param('name', header='content-disposition'):
                part.get_payload(decode=True) for part in message.iter_parts()}

    def test_create_uploads_statement_testcases_and_solution(self):
        (self.directory / 'solution.md').write_text('## Ý tưởng\nCộng hai số.\n', encoding='utf-8')
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual([r[0] for r in self.requests], ['POST', 'POST', 'PUT'])
        self.assertTrue(all(r[2]['Authorization'] == 'Bearer test-api-key' for r in self.requests))
        payload = json.loads(self.requests[0][3])
        self.assertEqual(payload['code'], 'demo001')
        self.assertEqual(payload['name'], 'Tính tổng hai số')
        self.assertEqual(payload['description'], self.statement.split('\n', 1)[1])
        self.assertEqual(payload['time_limit'], 2.0)
        self.assertEqual(payload['memory_limit'], 65536)
        self.assertNotIn('is_public', payload)
        parts = self.multipart(self.requests[1])
        manifest = json.loads(parts['manifest'])
        self.assertEqual(manifest['checker'], 'standard')
        self.assertEqual([c['input_file'] for c in manifest['cases']],
                         ['example_00.in', 'example_01.in'])
        with zipfile.ZipFile(io.BytesIO(parts['upload'])) as archive:
            self.assertEqual(set(archive.namelist()),
                             {'example_00.in', 'example_00.out', 'example_01.in', 'example_01.out'})
            self.assertEqual(archive.read('example_00.out'), b'3\n')
        self.assertEqual(json.loads(self.requests[2][3]), {'content': '## Ý tưởng\nCộng hai số.\n'})
        self.assertTrue((self.directory / 'in' / 'example_00.in').exists())
        self.assertFalse((self.directory / 'DEMO001.zip').exists())

    def test_conflict_updates_existing_problem(self):
        self.statuses = [409, 200, 200]
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual([(r[0], r[1]) for r in self.requests], [
            ('POST', '/api/v3/problem-import/problems'),
            ('PATCH', '/api/v3/problem-import/problems/demo001'),
            ('POST', '/api/v3/problem-import/problems/demo001/testcases')])
        self.assertNotIn('code', json.loads(self.requests[1][3]))

    def test_skip_statement_uploads_only_testcases_and_editorial(self):
        (self.directory / 'task.md').unlink()
        (self.directory / 'solution.md').write_text('Updated editorial')
        self.problem.config['upload'] = {'checker': 'identical'}
        ProblemUpload(self.problem, skip_statement=True).upload(self.client)
        self.assertEqual([(r[0], r[1]) for r in self.requests], [
            ('POST', '/api/v3/problem-import/problems/demo001/testcases'),
            ('PUT', '/api/v3/problem-import/problems/demo001/editorial')])
        parts = self.multipart(self.requests[0])
        self.assertEqual(json.loads(parts['manifest'])['checker'], 'identical')
        with zipfile.ZipFile(io.BytesIO(parts['upload'])) as archive:
            self.assertEqual(len(archive.namelist()), 4)
            self.assertEqual(archive.read('example_00.out'), b'3\n')
        self.assertEqual(json.loads(self.requests[1][3]), {'content': 'Updated editorial'})

    def test_skip_statement_missing_remote_problem_stops_without_creating(self):
        (self.directory / 'solution.md').write_text('Editorial')
        self.statuses = [404]
        with self.assertRaises(UploadError) as caught:
            ProblemUpload(self.problem, skip_statement=True).upload(self.client)
        self.assertEqual(caught.exception.status, 404)
        self.assertEqual([(r[0], r[1]) for r in self.requests], [
            ('POST', '/api/v3/problem-import/problems/demo001/testcases')])

    def test_editorial_takes_priority(self):
        (self.directory / 'solution.md').write_text('fallback')
        (self.directory / 'editorial.md').write_text('preferred')
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(json.loads(self.requests[-1][3]), {'content': 'preferred'})

    def test_custom_manifest(self):
        manifest = {'checker': 'floats', 'checker_args': {'precision': 6}, 'cases': [
            {'type': 'S', 'points': 100},
            {'input_file': 'example_01.in', 'output_file': 'example_01.out'},
            {'input_file': 'example_00.in', 'output_file': 'example_00.out'}, {'type': 'E'}]}
        (self.directory / 'manifest.json').write_text(json.dumps(manifest))
        self.problem.config['upload']['manifest'] = 'manifest.json'
        self.problem.write_hashes()
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(json.loads(self.multipart(self.requests[1])['manifest']), manifest)

    def custom_checker(self, extension='.cpp', source=None, **settings):
        if source is None:
            source = b'// UTF-8 checker: \xc4\x91\xc3\xbang\nint main() { return 0; }\n'
        path = self.directory / ('checker' + extension)
        path.write_bytes(source)
        self.problem.config['upload'].update(checker='custom', **settings)
        if extension != '.cpp':
            self.problem.config['upload']['custom_checker'] = path.name
        return path, source

    def test_custom_cpp_checker_uploaded_before_testcases(self):
        checker, source = self.custom_checker(checker_args={'time_limit': 3})
        (self.directory / 'solution.md').write_text('Editorial')
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual([(r[0], r[1]) for r in self.requests], [
            ('POST', '/api/v3/problem-import/problems'),
            ('POST', '/api/v3/problem-import/problems/demo001/checker'),
            ('POST', '/api/v3/problem-import/problems/demo001/testcases'),
            ('PUT', '/api/v3/problem-import/problems/demo001/editorial')])
        self.assertTrue(all(r[2]['Authorization'] == 'Bearer test-api-key' for r in self.requests))
        fields = self.multipart(self.requests[1])
        self.assertEqual(set(fields), {'upload', 'checker_args'})
        self.assertEqual(fields['upload'], source)
        self.assertEqual(json.loads(fields['checker_args']), {'time_limit': 3})
        self.assertIn(b'filename="checker.cpp"', self.requests[1][3])
        manifest = json.loads(self.multipart(self.requests[2])['manifest'])
        self.assertNotIn('checker', manifest)
        self.assertNotIn('checker_args', manifest)
        self.assertEqual(len(manifest['cases']), 2)
        self.assertNotIn('checker_args', json.loads(self.requests[0][3]))
        self.assertNotIn('custom_checker', json.loads(self.requests[0][3]))
        with zipfile.ZipFile(io.BytesIO(self.multipart(self.requests[2])['upload'])) as archive:
            self.assertEqual(len(archive.namelist()), 4)
            self.assertNotIn(checker.name, archive.namelist())

    def test_custom_python_checker_uses_python_filename_and_empty_args(self):
        _, source = self.custom_checker('.py', b'def check(process_output, judge_output, **kwargs):\n    return True\n')
        ProblemUpload(self.problem).upload(self.client)
        fields = self.multipart(self.requests[1])
        self.assertIn(b'filename="checker.py"', self.requests[1][3])
        self.assertEqual(fields['upload'], source)
        self.assertEqual(json.loads(fields['checker_args']), {})
        self.assertNotIn('checker', json.loads(self.multipart(self.requests[2])['manifest']))

    def test_custom_checker_uses_problem_checker_path(self):
        path = self.directory / 'gen' / 'output.cpp'
        path.write_text('int main() {}\n')
        self.problem.checker = path
        self.problem.config['upload']['checker'] = 'bridged'
        upload = ProblemUpload(self.problem)
        self.assertEqual(upload.custom_checker, path)
        self.assertEqual(upload.checker_source, path.read_bytes())

    def test_explicit_custom_checker_path_without_checker_name(self):
        path, _ = self.custom_checker()
        del self.problem.config['upload']['checker']
        self.problem.config['upload']['custom_checker'] = path.name
        upload = ProblemUpload(self.problem)
        self.assertEqual(upload.custom_checker, path)
        self.assertNotIn('checker', upload.manifest)

    def test_custom_checker_manifest_preserves_cases_and_overrides_args(self):
        self.custom_checker(checker_args={'time_limit': 2})
        manifest = {'checker': 'bridged', 'checker_args': {'time_limit': 3},
                    'output_limit': 64, 'cases': [
                        {'type': 'S', 'points': 100},
                        {'input_file': 'example_01.in', 'output_file': 'example_01.out'},
                        {'input_file': 'example_00.in', 'output_file': 'example_00.out',
                         'checker': 'identical'}, {'type': 'E'}]}
        (self.directory / 'manifest.json').write_text(json.dumps(manifest))
        self.problem.config['upload']['manifest'] = 'manifest.json'
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(json.loads(self.multipart(self.requests[1])['checker_args']), {'time_limit': 3})
        sent = json.loads(self.multipart(self.requests[2])['manifest'])
        self.assertEqual(sent, {key: value for key, value in manifest.items()
                                if key not in ('checker', 'checker_args')})
        self.assertEqual(json.loads((self.directory / 'manifest.json').read_text()), manifest)

    def test_skip_statement_also_uploads_custom_checker(self):
        self.custom_checker()
        (self.directory / 'task.md').unlink()
        ProblemUpload(self.problem, skip_statement=True).upload(self.client)
        self.assertEqual([r[1] for r in self.requests], [
            '/api/v3/problem-import/problems/demo001/checker',
            '/api/v3/problem-import/problems/demo001/testcases'])

    def test_checker_failure_stops_before_testcases_and_editorial(self):
        self.custom_checker()
        (self.directory / 'solution.md').write_text('Editorial')
        self.statuses = [201, 409]
        with self.assertRaises(UploadError) as caught:
            ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(caught.exception.status, 409)
        self.assertEqual(len(self.requests), 2)
        self.assertTrue(self.requests[-1][1].endswith('/checker'))

    def test_custom_checker_update_follows_problem_conflict(self):
        self.custom_checker()
        self.statuses = [409, 200, 200, 200]
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual([r[0] for r in self.requests], ['POST', 'PATCH', 'POST', 'POST'])
        self.assertTrue(self.requests[2][1].endswith('/checker'))

    def test_invalid_custom_checker_rejected_before_requests(self):
        path, _ = self.custom_checker()
        for content, message in [(b'', 'empty'), (b' \n', 'empty'), (b'\xff', 'UTF-8'),
                                 (b'int main() {}\x00', 'NUL'),
                                 (b'x'*(MAX_CHECKER_BYTES+1), '1 MiB')]:
            with self.subTest(message=message):
                path.write_bytes(content)
                with self.assertRaisesRegex(UploadError, message):
                    ProblemUpload(self.problem)
        path.unlink()
        with self.assertRaisesRegex(UploadError, 'Cannot read custom checker'):
            ProblemUpload(self.problem)
        path = self.directory / 'checker.txt'
        path.write_text('content')
        self.problem.config['upload']['custom_checker'] = path.name
        with self.assertRaisesRegex(UploadError, r'\.cpp or \.py'):
            ProblemUpload(self.problem)
        self.assertEqual(self.requests, [])

    def test_custom_checker_accepts_source_at_size_limit(self):
        path, source = self.custom_checker(source=b'x'*MAX_CHECKER_BYTES)
        upload = ProblemUpload(self.problem)
        self.assertEqual(upload.custom_checker, path)
        self.assertEqual(upload.checker_source, source)

    def test_invalid_checker_settings_rejected_before_requests(self):
        self.custom_checker()
        settings = self.problem.config['upload']
        for args in (None, [], 'args', {'time_limit': float('nan')}, {'bad': b'bytes'}):
            with self.subTest(args=args):
                settings['checker_args'] = args
                with self.assertRaisesRegex(UploadError, 'JSON object'):
                    ProblemUpload(self.problem)
        settings.pop('checker_args')
        for source in ('', False, []):
            with self.subTest(source=source):
                settings['custom_checker'] = source
                with self.assertRaisesRegex(UploadError, 'source file path'):
                    ProblemUpload(self.problem)
        settings.pop('custom_checker')
        for checker in ([], {}, 3, 'unknown'):
            with self.subTest(checker=checker):
                settings['checker'] = checker
                with self.assertRaises(UploadError):
                    ProblemUpload(self.problem)
        self.assertEqual(self.requests, [])

    def test_custom_source_conflicts_with_builtin_checker(self):
        path, _ = self.custom_checker()
        self.problem.config['upload'].update(checker='standard', custom_checker=path.name)
        with self.assertRaisesRegex(UploadError, 'conflicts'):
            ProblemUpload(self.problem)

    def test_custom_manifest_cannot_reset_the_uploaded_checker(self):
        self.custom_checker()
        (self.directory / 'manifest.json').write_text(json.dumps({'checker': 'standard', 'cases': []}))
        self.problem.config['upload']['manifest'] = 'manifest.json'
        with self.assertRaisesRegex(UploadError, 'conflicts'):
            ProblemUpload(self.problem)

    def test_builtin_checker_args_do_not_upload_a_source(self):
        self.problem.config['upload'].update(checker='floats', checker_args={'precision': 6})
        ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(len(self.requests), 2)
        manifest = json.loads(self.multipart(self.requests[1])['manifest'])
        self.assertEqual(manifest['checker'], 'floats')
        self.assertEqual(manifest['checker_args'], {'precision': 6})

    def test_http_failure_stops_and_redacts_key(self):
        self.statuses = [401]
        self.error_body = b'{"detail":"test-api-key is invalid"}'
        with self.assertRaises(UploadError) as caught:
            ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(caught.exception.status, 401)
        self.assertNotIn('test-api-key', str(caught.exception))
        self.assertIn('[REDACTED]', str(caught.exception))
        self.assertEqual(len(self.requests), 1)

    def test_testcase_failure_does_not_upload_editorial(self):
        (self.directory / 'editorial.md').write_text('editorial')
        self.statuses = [201, 413]
        with self.assertRaises(UploadError):
            ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(len(self.requests), 2)

    def test_redirect_is_not_followed(self):
        self.statuses = [302]
        with self.assertRaises(UploadError):
            ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(len(self.requests), 1)

    def test_stale_hash_rejected_before_requests(self):
        (self.directory / 'out' / 'example_00.out').write_text('wrong\n')
        for skip_statement in (False, True):
            with self.subTest(skip_statement=skip_statement), \
                    self.assertRaisesRegex(RuntimeError, 'hashes are different'):
                ProblemUpload(self.problem, skip_statement=skip_statement).upload(self.client)
        self.assertEqual(self.requests, [])

    def test_missing_testcase_rejected_before_requests(self):
        (self.directory / 'out' / 'example_00.out').unlink()
        self.problem.ignore_warning = True
        self.problem.write_hashes()
        with self.assertRaisesRegex(UploadError, 'Missing testcase'):
            ProblemUpload(self.problem).upload(self.client)
        self.assertEqual(self.requests, [])

    def test_missing_required_metadata(self):
        del self.problem.config['upload']['group']
        with self.assertRaisesRegex(UploadError, 'group'):
            ProblemUpload(self.problem)
        self.assertEqual(self.requests, [])

    def test_invalid_folder_code(self):
        self.problem.basedir = self.root / 'invalid_code'
        with self.assertRaisesRegex(UploadError, 'directory name'):
            ProblemUpload(self.problem)

    def test_no_heading_uses_toml_title_and_preserves_statement(self):
        content = '### Đề bài\nNội dung không có tiêu đề cấp một.\n'
        (self.directory / 'task.md').write_text(content, encoding='utf-8')
        upload = ProblemUpload(self.problem)
        self.assertEqual(upload.payload['name'], 'Ignored TOML title')
        self.assertEqual(upload.payload['description'], content)

    def test_first_h1_only_and_ignore_fenced_code(self):
        content = '```text\n# code\n```\n## section\n# Tên bài ###\nBody\n# Later\n'
        (self.directory / 'task.md').write_text(content, encoding='utf-8')
        upload = ProblemUpload(self.problem)
        self.assertEqual(upload.payload['name'], 'Tên bài')
        self.assertEqual(upload.payload['description'], content.replace('# Tên bài ###\n', ''))

    def test_missing_name_reports_statement_or_title(self):
        (self.directory / 'task.md').write_text('Body without a heading.\n')
        del self.problem.config['title']
        with self.assertRaisesRegex(UploadError, 'heading.*title'):
            ProblemUpload(self.problem)

    def test_env_and_host_normalization(self):
        with patch.dict(os.environ, {'HOST': self.host, 'PROBLEM_IMPORT_API_KEY': 'key'}):
            self.assertEqual(UploadClient.from_env().base_url, self.host + '/api/v3/problem-import')
        self.assertEqual(UploadClient('judge.example.com', 'key').base_url,
                         'https://judge.example.com/api/v3/problem-import')
        self.assertEqual(UploadClient(self.host + '/api/v3/problem-import/', 'key').base_url,
                         self.client.base_url)
        for host in ('', 'ftp://example.com', 'https://user:pass@example.com',
                     'https://example.com?key=secret', 'https://example.com/other'):
            with self.subTest(host=host), self.assertRaises(UploadError):
                UploadClient(host, 'key')

    def run_cli(self, *args, key='test-api-key'):
        env = dict(os.environ, HOST=self.host, PROBLEM_IMPORT_API_KEY=key)
        return subprocess.run([sys.executable, str(Path(generate.__file__).resolve())] + list(args),
                              env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                              timeout=30)

    def test_cli_generates_and_uploads_without_html(self):
        self.problem.clean()
        result = self.run_cli(str(self.directory / 'info.toml'), '-u')
        self.assertEqual(result.returncode, 0, result.stderr.decode())
        self.assertEqual(len(self.requests), 2)
        self.assertFalse((self.directory / 'task.html').exists())
        self.problem.assert_hashes()

    def test_cli_skip_statement_generates_and_uploads_without_local_statement(self):
        (self.directory / 'task.md').unlink()
        self.problem.clean()
        result = self.run_cli(str(self.directory / 'info.toml'), '-u', '--skip-statement')
        self.assertEqual(result.returncode, 0, result.stderr.decode())
        self.assertEqual([(r[0], r[1]) for r in self.requests], [
            ('POST', '/api/v3/problem-import/problems/demo001/testcases')])
        self.assertFalse((self.directory / 'task.html').exists())
        self.problem.assert_hashes()

    def test_cli_custom_checker_upload_with_skip_statement(self):
        self.custom_checker()
        config = self.directory / 'info.toml'
        config.write_text(config.read_text().replace('[upload]',
                          "[upload]\nchecker = 'custom'\nchecker_args = {time_limit = 3}"))
        (self.directory / 'task.md').unlink()
        self.problem.clean()
        result = self.run_cli(str(config), '-u', '--skip-statement')
        self.assertEqual(result.returncode, 0, result.stderr.decode())
        self.assertEqual([r[1] for r in self.requests], [
            '/api/v3/problem-import/problems/demo001/checker',
            '/api/v3/problem-import/problems/demo001/testcases'])
        self.assertEqual(json.loads(self.multipart(self.requests[0])['checker_args']), {'time_limit': 3})
        self.problem.assert_hashes()
        self.assertFalse((self.directory / 'task.html').exists())

    def test_cli_missing_key_fails_before_generating(self):
        self.problem.clean()
        result = self.run_cli(str(self.directory / 'info.toml'), '--upload', key='')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn(b'PROBLEM_IMPORT_API_KEY', result.stderr)
        self.assertFalse((self.directory / 'in').exists())
        self.assertEqual(self.requests, [])

    def test_cli_upload_names_and_deduplication(self):
        with patch.dict(os.environ, {'HOST': self.host, 'PROBLEM_IMPORT_API_KEY': 'test-api-key'}), \
                patch.object(generate, 'find_problem_dir', return_value=self.directory), \
                patch.object(Problem, 'generate') as generation:
            generate.main(['-p', 'DEMO001', '-u', 'DEMO001'])
        self.assertEqual(generation.call_count, 1)
        self.assertEqual(len(self.requests), 2)

    def test_cli_rejects_conflicting_modes_and_empty_selection(self):
        for args in (['-u'], ['-u', '--clean'], ['-u', '--dev'], ['-u', '--test'],
                     ['-u', '--only-html'], ['-u', '-z', 'DEMO001'],
                     ['--skip-statement'], ['-p', 'DEMO001', '--skip-statement']):
            with self.subTest(args=args):
                result = self.run_cli(*args)
                self.assertNotEqual(result.returncode, 0)
        self.assertEqual(self.requests, [])


if __name__ == '__main__':
    unittest.main()
