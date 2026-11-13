"""Generate and audit actual binary inputs without invoking HTML export."""
from pathlib import Path
import argparse
import concurrent.futures
import hashlib
import json
import os
import random
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import time

from model import TITLES, FORMATS, HEADERS, EXAMPLES, encode, decode, oracle

ROOT = Path(__file__).resolve().parents[2]
GROUPS = [('edge', 8), ('small', 6), ('random', 6), ('max', 3)]


def compile_source(source, standard='c++11', output=None):
    output = output or source.with_suffix('')
    args = [os.environ.get('CXX', 'g++'), '-O2', '-std=' + standard, '-Wall', '-Wextra',
            '-Werror', '-Wno-unused-result', '-I', str(ROOT / 'common'), str(source), '-o', str(output)]
    result = subprocess.run(args, capture_output=True)
    if result.returncode:
        raise AssertionError(result.stderr.decode())
    return output


def run_binary(exe, path, expect=0, file_io=None):
    if file_io is not None:
        input_name, output_name = file_io
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            shutil.copyfile(path, directory / input_name)
            started = time.perf_counter()
            result = subprocess.run([str(exe.resolve())], cwd=directory,
                                    stdin=subprocess.DEVNULL, capture_output=True, timeout=1.0)
            elapsed = time.perf_counter() - started
            assert result.returncode == 0, result.stderr
            assert result.stdout == b'', 'The solution must write its named output file'
            output = directory / output_name
            assert output.is_file(), f'Missing output file {output_name}'
            return output.read_bytes(), elapsed
    started = time.perf_counter()
    with path.open('rb') as stream:
        result = subprocess.run([str(exe)], stdin=stream, capture_output=True, timeout=1.0)
    elapsed = time.perf_counter() - started
    if expect == 0:
        assert result.returncode == 0, result.stderr
    else:
        assert result.returncode != 0, 'Verifier accepted invalid input'
    return result.stdout, elapsed


def run_checker(base, inp, actual, expected, accept):
    result = subprocess.run([str(base / 'checker'), str(inp), str(actual), str(expected)],
                            capture_output=True, timeout=1.0)
    assert (result.returncode == 0) == accept, result.stderr


def audit_statement(base, kind):
    s = (base / 'task.md').read_text()
    expected = ['### Đề bài', '### Dữ liệu vào', '### Dữ liệu ra', '### Ràng buộc',
                '### Sample Input 1', '### Sample Output 1',
                '### Sample Input 2', '### Sample Output 2', '### Giải thích']
    assert s.splitlines()[0] == f'# {base.name.upper()} — {TITLES[kind - 1]}'
    assert re.findall(r'^### .+$', s, re.M) == expected
    assert not re.search(r'^#{1,2} ', s[s.index('\n'):], re.M)
    assert not re.search(r'\b\w+_t\b', s)
    assert '#pragma' not in s
    input_name, output_name = base.name.upper() + '.INP', base.name.upper() + '.OUT'
    assert f'**`{input_name}`**' in s and f'**`{output_name}`**' in s
    assert 'stdin' not in s and 'stdout' not in s
    assert '### Subtask' not in s
    solution = (base / 'solution.md').read_text()
    assert not re.search(r'^# ', solution, re.M)
    assert not re.search(r'kiểm thử|oracle|verifier|checker|benchmark', solution, re.I)
    assert not re.search(r'\b\w+_t\b', solution)
    assert '#pragma' not in solution
    source = (base / 'sol/correct.cpp').read_text()
    assert f'ifstream fin("{input_name}", ios::binary)' in source
    assert f'ofstream fout("{output_name}")' in source
    assert not re.search(r'\b(cin|cout|stdin|stdout)\b', source)
    assert '```cpp\n' + (base / 'sol/correct.cpp').read_text() + '```' in solution
    sys.path.insert(0, str(ROOT))
    import toml
    config = toml.load(base / 'info.toml')
    assert config['timelimit'] == 1
    assert config['upload'] == dict(time_limit=1, group='01', classes='A',
        types=['intro_files'], partial=True, allowed_languages=['CPP11', 'CPP14', 'CPP17', 'CPP20'],
        io_method='file', io_input_file=input_name, io_output_file=output_name, binary_data=True)
    assert config['tests'] == [dict(name='example.in', number=2)] + [
        dict(name=name + '.cpp', number=count) for name, count in GROUPS]
    for j, (h, rows) in enumerate(EXAMPLES[kind - 1], 1):
        raw = encode(kind, h, rows)
        displayed = re.search(rf'### Sample Input {j}\n\n```text\n(.*?)\n```', s, re.S)[1]
        answer = re.search(rf'### Sample Output {j}\n\n```text\n(.*?)\n```', s, re.S)[1]
        assert bytes.fromhex(displayed) == raw
        assert (base / 'gen' / f'example_{j-1:02d}.in').read_bytes() == raw
        assert answer.split() == oracle(kind, raw).split()


def random_case(kind, rng):
    n = rng.randrange(0 if kind in (1, 8) else 1, 16)
    h = () if kind in (1, 8) else (b'A109', n) if kind == 10 else (
        n, rng.randrange(11)) if kind == 2 else (n, rng.choice([-10**12, 0, 10**12])) if kind == 5 else (n,)
    def code(width):
        return bytes(rng.randrange(65, 91) for _ in range(rng.randrange(1, width + 1)))
    def val(): return rng.choice([-10**9, -26, -13, -10, -1, 0, 1, 10, 13, 26, 10**9])
    rows = []
    for _ in range(n):
        if kind == 1: row = (rng.randrange(1, 100), val())
        elif kind == 2: row = (rng.randrange(1, 100), rng.randrange(11))
        elif kind == 3: row = (rng.randrange(1, 100), rng.choice([0, 1, 10000]), rng.choice([0, 1, 10**9]))
        elif kind == 4: row = (code(8), rng.randrange(11), rng.randrange(11), rng.randrange(11))
        elif kind == 5: row = (rng.randrange(1, 3), rng.choice([0, 1, 10, 13, 26, 10**9]))
        elif kind == 6: row = (rng.randrange(1, 4), rng.choice([0, 1, 10**9]))
        elif kind == 7: row = (val(), val())
        elif kind == 8: row = (rng.choice([b'R', b'S']), rng.choice([0, 1, 10, 13, 26, 10**9]))
        elif kind == 9: row = (code(12), rng.choice([0, 1, 10**9]))
        else: row = (rng.randrange(2000, 2101), rng.randrange(1, 13), rng.randrange(1, 29), rng.randrange(-100, 101))
        rows.append(row)
    return encode(kind, h, rows)


def invalid_cases(kind):
    h, rows = EXAMPLES[kind - 1][0]
    raw = encode(kind, h, rows)
    result = [raw[:-1], raw + b'\x00']
    if kind not in (1, 8):
        zero = list(h)
        zero[1 if kind == 10 else 0] = 0
        result += [encode(kind, zero, []), b'']
        huge = list(h)
        huge[1 if kind == 10 else 0] = 200001
        result.append(encode(kind, huge, []))
    else:
        result.append(encode(kind, (), [rows[0]] * 200001))
    # Every field's range and fixed string padding is checked independently.
    mutations = {
        1: [(0, 0), (1, -1000000001), (1, 1000000001)],
        2: [(0, 0), (1, -1), (1, 11)],
        3: [(0, 0), (1, -1), (1, 10001), (2, -1), (2, 1000000001)],
        4: [(0, b''), (0, b'a'), (0, b'A\x00B'), (1, -1), (2, 11), (3, 11)],
        5: [(0, 0), (0, 3), (1, -1), (1, 1000000001)],
        6: [(0, 0), (0, 4), (1, -1), (1, 1000000001)],
        7: [(0, -1000000001), (0, 1000000001), (1, -1000000001), (1, 1000000001)],
        8: [(0, b'X'), (1, -1), (1, 1000000001)],
        9: [(0, b''), (0, b'a'), (0, b'A\x00B'), (1, -1), (1, 1000000001)],
        10: [(0, 1999), (0, 2101), (1, 0), (1, 13), (2, 0), (2, 29), (3, -101), (3, 101)],
    }
    for field, value in mutations[kind]:
        changed = list(rows[0]); changed[field] = value
        result.append(encode(kind, h, [tuple(changed)] + rows[1:]))
    if kind == 2:
        result += [encode(kind, (h[0], t), rows) for t in (-1, 11)]
    if kind == 5:
        result += [encode(kind, (h[0], b), rows) for b in (-10**12-1, 10**12+1)]
    if kind == 10: result.append(encode(kind, (b'BAD!', h[1]), rows))
    return result


def audit_problem(kind, update_hashes):
    base = ROOT / 'custom' / f'a109{kind:06d}'
    file_io = (base.name.upper() + '.INP', base.name.upper() + '.OUT')
    audit_statement(base, kind)
    sources = [base / 'sol/correct.cpp', base / 'checker.cpp', base / 'verifier.cpp'] + [
        base / 'gen' / (name + '.cpp') for name, _ in GROUPS]
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(compile_source, sources))
    for sub in ('in', 'out'):
        (base / sub).mkdir(exist_ok=True)
    files = []
    for j in range(2):
        name = f'example_{j:02d}.in'
        (base / 'in' / name).write_bytes((base / 'gen' / name).read_bytes())
        files.append(name)
    for name, count in GROUPS:
        for seed in range(count):
            path = base / 'in' / f'{name}_{seed:02d}.in'
            with path.open('wb') as output:
                subprocess.run([str(base / 'gen' / name), str(seed)], stdout=output, check=True, timeout=10)
            files.append(path.name)
        # Reproducibility, including the largest format.
        again = subprocess.check_output([str(base / 'gen' / name), '0'], timeout=10)
        assert again == (base / 'in' / f'{name}_00.in').read_bytes()
    expected_in = set(files)
    assert {p.name for p in (base / 'in').glob('*.in')} == expected_in
    slowest = 0
    hashes = {}
    for name in files:
        inp = base / 'in' / name
        raw = inp.read_bytes()
        decode(kind, raw)
        run_binary(base / 'verifier', inp)
        answer, elapsed = run_binary(base / 'sol/correct', inp, file_io=file_io)
        slowest = max(slowest, elapsed)
        expected = oracle(kind, raw).encode()
        assert answer == expected, (base.name, name, answer[:200], expected[:200])
        out = base / 'out' / (inp.stem + '.out')
        out.write_bytes(expected)
        run_checker(base, inp, out, out, True)
        hashes[name] = hashlib.sha256(raw).hexdigest()
        hashes[out.name] = hashlib.sha256(expected).hexdigest()
    with tempfile.TemporaryDirectory() as temp:
        temp = Path(temp)
        inp = temp / 'data.in'
        # Compile and exercise every advertised language version on an actual binary file.
        sample = encode(kind, *EXAMPLES[kind - 1][0])
        inp.write_bytes(sample)
        for standard in ('c++14', 'c++17', 'c++20'):
            exe = compile_source(base / 'sol/correct.cpp', standard, temp / standard)
            answer, _ = run_binary(exe, inp, file_io=file_io)
            assert answer == oracle(kind, sample).encode()
        rng = random.Random(1090000 + kind)
        for _ in range(60):
            raw = random_case(kind, rng)
            inp.write_bytes(raw)
            run_binary(base / 'verifier', inp)
            answer, _ = run_binary(base / 'sol/correct', inp, file_io=file_io)
            assert answer == oracle(kind, raw).encode()
        # Ordinary struct padding is not part of a field and may contain any bytes.
        if kind in (5, 6, 8):
            padded = bytearray(sample)
            hs = struct.calcsize(HEADERS[kind - 1])
            rs = struct.calcsize(FORMATS[kind - 1])
            offsets = list(range(4, 8)) if kind == 5 else []
            width = 7 if kind == 5 else 3
            for pos in range(hs, len(padded), rs):
                offsets.extend(range(pos + 1, pos + 1 + width))
            for pos in offsets:
                padded[pos] = rng.choice([10, 13, 26, 255])
            inp.write_bytes(padded)
            run_binary(base / 'verifier', inp)
            answer, _ = run_binary(base / 'sol/correct', inp, file_io=file_io)
            assert answer == oracle(kind, sample).encode()
        for raw in invalid_cases(kind):
            inp.write_bytes(raw)
            run_binary(base / 'verifier', inp, expect=1)
        inp.write_bytes(sample)
        expected = temp / 'expected.out'
        expected.write_text(oracle(kind, sample))
        actual = temp / 'actual.out'
        tokens = expected.read_text().split()
        for text, ok in [(' \n\t'.join(tokens) + '\n', True),
                         ('WRONG\n', False), (' '.join(tokens[:-1]), False),
                         (' '.join(tokens + ['EXTRA']), False)]:
            actual.write_text(text)
            run_checker(base, inp, actual, expected, ok)
    hp = base / 'hash.json'
    if update_hashes:
        hp.write_text(json.dumps(hashes, indent=2, sort_keys=True) + '\n')
    else:
        assert json.loads(hp.read_text()) == hashes, f'Hash mismatch: {base.name}'
    print(f'{base.name}: 25 binary tests + 60 random cases, verifier/checker OK; '
          f'C++11/14/17/20 OK; max {slowest:.3f}s (limit 1s)', flush=True)
    return slowest


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--problem', choices=[f'a109{k:06d}' for k in range(1, 11)])
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    kinds = [int(args.problem[-6:])] if args.problem else range(1, 11)
    for k in kinds:
        audit_problem(k, args.update_hashes)
