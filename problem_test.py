#!/usr/bin/env python3

import unittest
import json
import platform
import sys
from pathlib import Path
from subprocess import CalledProcessError, TimeoutExpired
from tempfile import TemporaryDirectory
from unittest.mock import patch
from logging import basicConfig, getLogger
from os import getenv
from problem import Problem, check_call_to_file, param_to_str

logger = getLogger(__name__)

class TestParam(unittest.TestCase):
    # select problem by problem id
    def test_convert_integer(self):
        self.assertEqual(param_to_str('A', 100), "#define A (long long)100")
        self.assertEqual(param_to_str('A', 1_000_000_007), "#define A (long long)1000000007")
        self.assertEqual(param_to_str('A', 998244353), "#define A (long long)998244353")


class TestFileIO(unittest.TestCase):
    def setUp(self):
        self.temp = TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.base = self.root / 'demo'
        self.base.mkdir()
        for folder in ('in', 'out', 'sol'):
            (self.base / folder).mkdir()
        (self.base / 'info.toml').write_text('''title = 'Demo'
timelimit = 1.0
checker = 'checker.py'
[[tests]]
name = 'example.in'
number = 2
[[solutions]]
type = 'correct'
name = 'correct.py'
[upload]
io_method = 'file'
io_input_file = 'DEMO.INP'
io_output_file = 'DEMO.OUT'
''')
        self.problem = Problem(self.root, self.base)
        self.solution = self.base / 'sol/correct.py'
        self.solution.write_text('''from pathlib import Path
import sys
assert sys.stdin.buffer.read() == b''
data = Path('DEMO.INP').read_bytes()
Path('DEMO.OUT').write_bytes(data[::-1])
print('diagnostic output is not the answer')
''')
        self.data = [b'\x00\x0a\x0d\x1a\xff', b'\x00\xff']
        for i, raw in enumerate(self.data):
            (self.base / 'in' / f'example_{i:02d}.in').write_bytes(raw)

    def test_generation_and_judging_use_named_files_and_preserve_bytes(self):
        (self.base / 'checker.py').write_text('''from pathlib import Path
import sys
sys.exit(0 if Path(sys.argv[2]).read_bytes() == Path(sys.argv[3]).read_bytes() else 1)
''')
        self.problem.make_outputs(True)
        for i, raw in enumerate(self.data):
            self.assertEqual((self.base / 'out' / f'example_{i:02d}.out').read_bytes(), raw[::-1])
        self.problem.judge(self.solution, {})
        self.assertFalse((self.base / 'DEMO.INP').exists())
        self.assertFalse((self.base / 'DEMO.OUT').exists())

    def test_missing_output_is_rejected(self):
        self.solution.write_text("print('not an output file')\n")
        with self.assertRaises(CalledProcessError):
            self.problem.run_solution(self.solution, self.base / 'in/example_00.in', self.base / 'out/answer.out')

    def test_file_solution_obeys_timeout(self):
        self.solution.write_text('while True: pass\n')
        with self.assertRaises(TimeoutExpired):
            self.problem.run_solution(self.solution, self.base / 'in/example_00.in',
                                      self.base / 'out/answer.out', timeout=0.1)

    def test_invalid_filenames_rejected_before_running(self):
        for name in ('../escaped', 'subdir/file', 'subdir\\file', '.', '', 'bad\x00name'):
            with self.subTest(name=name), self.assertRaises(ValueError):
                self.problem.config['upload']['io_input_file'] = name
                self.problem.run_solution(self.solution, self.base / 'in/example_00.in',
                                          self.base / 'out/answer.out')

    def test_standard_solution_still_uses_standard_streams(self):
        self.problem.config['upload']['io_method'] = 'standard'
        self.solution.write_text('import sys\nprint(sum(sys.stdin.buffer.read()))\n')
        output = self.base / 'out/answer.out'
        self.problem.run_solution(self.solution, self.base / 'in/example_00.in', output, timeout=1)
        self.assertEqual(output.read_text(), str(sum(self.data[0])) + '\n')

    def test_binary_generation_skips_windows_text_normalization(self):
        self.problem.config['upload']['binary_data'] = True
        (self.base / 'gen').mkdir()
        for i, raw in enumerate(self.data):
            (self.base / 'gen' / f'example_{i:02d}.in').write_bytes(raw)
        system = platform.system()
        with patch('problem.platform.uname') as uname, patch('problem.platform.system', return_value=system):
            uname.return_value.system = 'Windows'
            self.problem.make_inputs()
        for i, raw in enumerate(self.data):
            self.assertEqual((self.base / 'in' / f'example_{i:02d}.in').read_bytes(), raw)

    def test_binary_standard_output_keeps_control_and_non_utf8_bytes(self):
        self.problem.config['upload'].update(io_method='standard', binary_data=True)
        self.solution.write_text('import sys\nsys.stdout.buffer.write(sys.stdin.buffer.read()[::-1])\n')
        output = self.base / 'out/answer.out'
        system = platform.system()
        with patch('problem.platform.uname') as uname, patch('problem.platform.system', return_value=system):
            uname.return_value.system = 'Windows'
            self.problem.run_solution(self.solution, self.base / 'in/example_00.in', output, timeout=1)
        self.assertEqual(output.read_bytes(), self.data[0][::-1])

    def test_text_normalization_still_applies_to_text_data(self):
        output = self.base / 'out/text.out'
        command = [sys.executable, '-c', "import sys; sys.stdout.buffer.write(b'a\\r\\nb\\rc\\n')"]
        with patch('problem.platform.uname') as uname:
            uname.return_value.system = 'Windows'
            check_call_to_file(command, output)
        self.assertEqual(output.read_bytes(), b'a\nb\nc\n')

    def test_binary_data_manifest_precedence(self):
        self.problem.config['upload'].update(binary_data=False, manifest='manifest.json')
        (self.base / 'manifest.json').write_text(json.dumps({'binary_data': True}))
        self.assertTrue(self.problem.binary_data())
        (self.base / 'manifest.json').write_text('{}')
        self.assertFalse(self.problem.binary_data())

if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    unittest.main()
