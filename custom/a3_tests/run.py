#!/usr/bin/env python3
"""Build/validate the five A3 tasks without HTML; compare against tiny brute force."""
import argparse
from itertools import combinations
import hashlib
import json
import logging
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import zipfile

ROOT = Path(__file__).resolve().parents[2]
CODES = ('matha3', 'stringa3', 'bs13c', 'dpupstair03c', 'bs52c')
RNG = random.Random(20261019)
COUNTS = {code: 0 for code in CODES}


def run_solution(code, source, data):
    binary = ROOT / 'custom' / code / 'sol' / source
    result = subprocess.run([str(binary)], input=data, text=True,
                            capture_output=True, timeout=5, check=True)
    return result.stdout.split()


def compare(code, data, expected):
    expected = [str(x) for x in expected]
    for source in ('correct', 'reference'):
        actual = run_solution(code, source, data)
        assert actual == expected, (code, source, data, expected, actual)
    COUNTS[code] += 1


GROUP_SCORES = {
    'matha3': [60, 30, 10], 'stringa3': [50, 30, 20],
    'bs13c': [50, 50], 'dpupstair03c': [30, 20, 50], 'bs52c': [100],
}
SCORED_TESTS_PER_PROBLEM = 40
POINTS_PER_TEST = 2.5
GROUP_COUNTS = {code: [score * 2 // 5 for score in scores]
                for code, scores in GROUP_SCORES.items()}


def make_scoring_manifest(code):
    p = ROOT / 'custom' / code
    manifest = {'problem': code, 'scoring_mode': 'sum', 'max_score': 100,
                'points_per_test': POINTS_PER_TEST, 'sample_points': 0,
                'samples': [f.stem for f in sorted((p / 'gen').glob('example_*.in'))],
                'subtasks': []}
    for sub, points in enumerate(GROUP_SCORES[code], 1):
        files = sorted((p / 'in').glob(f'subtask{sub}_*.in'))
        assert len(files) == GROUP_COUNTS[code][sub-1], (code, sub, len(files))
        assert len(files) * POINTS_PER_TEST == points
        tests = [{'input': f.name, 'output': f.stem + '.out'} for f in files]
        manifest['subtasks'].append({'id': sub, 'score': points,
                                     'test_count': len(tests), 'tests': tests})
    return manifest


def write_scoring_files(code):
    p = ROOT / 'custom' / code
    manifest = make_scoring_manifest(code)
    (p / 'scoring.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n')
    text = f'# {code.upper()} — Phân điểm bộ test\n\n'
    text += ('Bài có **40 test chấm điểm**, mỗi test **2,5 điểm**, tổng **100 điểm**. '
             'Điểm bài là tổng điểm của các test trả lời đúng.\n\n'
             f'Gói `{code}.zip` chỉ chứa 40 cặp input/output chấm điểm. '
             'Khi nhập vào hệ thống chấm, đặt mỗi test 2,5 điểm trên thang 100. '
             'Các ví dụ `example_*` có 0 điểm và không nằm trong ZIP chấm điểm.\n\n'
             '| Subtask | Điểm | Số test | Tên input |\n| --- | --- | --- | --- |\n')
    for group in manifest['subtasks']:
        tests = group['tests']
        text += (f"| {group['id']} | {group['score']} | {group['test_count']} | "
                 f"`{tests[0]['input']}` đến `{tests[-1]['input']}` |\n")
    text += ('\nMỗi input có output cùng tên và đuôi `.out`. Mỗi test được gán đúng một subtask '
             'theo tên file; một test có thể đồng thời thỏa ràng buộc của nhiều subtask. '
             'Danh sách gán cụ thể cho từng file nằm trong `scoring.json`. '
             '`hash.json` đối chiếu cả test chấm điểm và ví dụ.\n')
    (p / 'scoring.md').write_text(text)
    with zipfile.ZipFile(p / (code + '.zip'), 'w', compression=zipfile.ZIP_DEFLATED) as archive:
        for group in manifest['subtasks']:
            for test in group['tests']:
                for directory, key in [('in', 'input'), ('out', 'output')]:
                    archive.write(p / directory / test[key], test[key])


def check_scoring_files():
    for code in CODES:
        p = ROOT / 'custom' / code
        expected = make_scoring_manifest(code)
        actual = json.loads((p / 'scoring.json').read_text())
        assert actual == expected, code
        scored = [test for group in actual['subtasks'] for test in group['tests']]
        names = [test[key] for test in scored for key in ('input', 'output')]
        assert len(scored) == len({test['input'] for test in scored}) == SCORED_TESTS_PER_PROBLEM
        assert sum(group['score'] for group in actual['subtasks']) == 100
        assert set((p / 'in').glob('*.in')) == {
            p / 'in' / test['input'] for test in scored
        } | {p / 'in' / (name + '.in') for name in actual['samples']}
        with zipfile.ZipFile(p / (code + '.zip')) as archive:
            assert len(archive.namelist()) == 2*SCORED_TESTS_PER_PROBLEM
            assert set(archive.namelist()) == set(names)
            for test in scored:
                for directory, key in [('in', 'input'), ('out', 'output')]:
                    assert archive.read(test[key]) == (p / directory / test[key]).read_bytes()
        print('PASS:', code, '40 scored tests, unique group assignments, 2.5 points/test, ZIP', flush=True)


def build(update_hashes=False):
    sys.path.insert(0, str(ROOT))
    from problem import Problem
    for code in CODES:
        print('Build:', code, flush=True)
        p = Problem(ROOT, ROOT / 'custom' / code)
        p.ignore_warning = bool(update_hashes)
        p.health_check()
        p.generate_params_h()
        p.compile_gens()
        p.compile_solutions()
        p.compile_verifier()
        p.compile_checker()
        for relative in ('gen/cases', 'sol/correct', 'sol/reference', 'verifier', 'checker'):
            assert (p.basedir / relative).is_file(), relative
        p.make_inputs()
        p.verify_inputs()
        p.make_outputs(True)
        for sol in p.config['solutions']:
            p.judge(p.basedir / 'sol' / sol['name'], sol)
        # Existing hashes must match. Initial generation may create the manifest.
        if update_hashes or not json.loads((p.basedir / 'hash.json').read_text()):
            p.write_hashes()
        p.assert_hashes()
        write_scoring_files(code)
        print('PASS:', code, 'generated tests, both solutions, hashes, ZIP', flush=True)


def check_artifacts():
    expected_headings = ['Đề bài', 'Dữ liệu vào', 'Dữ liệu ra', 'Ràng buộc', 'Subtask']
    for code in CODES:
        p = ROOT / 'custom' / code
        text = (p / 'task.md').read_text()
        assert text.startswith('# ' + code.upper() + ' — ')
        inputs = re.findall(r'### Sample Input (\d+)\n\n```text\n(.*?)\n```', text, re.S)
        outputs = re.findall(r'### Sample Output (\d+)\n\n```text\n(.*?)\n```', text, re.S)
        assert len(inputs) == len(outputs) >= 2
        headings = expected_headings[:]
        for i, ((ni, data), (no, answer)) in enumerate(zip(inputs, outputs), 1):
            assert int(ni) == int(no) == i
            headings += [f'Sample Input {i}', f'Sample Output {i}']
            assert (p / f'gen/example_{i-1:02}.in').read_text() == data + '\n'
            assert (p / f'out/example_{i-1:02}.out').read_text().split() == answer.split()
            compare(code, data + '\n', answer.split())
        headings += ['Giải thích']
        assert re.findall(r'^### (.+)$', text, re.M) == headings
        subtask_section = text.split('### Subtask\n', 1)[1].split('### Sample Input', 1)[0]
        rows = re.findall(r'^\| (\d+) \| (\d+)% \| (.+) \|$', subtask_section, re.M)
        expected_percentages = {
            'matha3': [60, 30, 10], 'stringa3': [50, 30, 20],
            'bs13c': [50, 50], 'dpupstair03c': [30, 20, 50], 'bs52c': [100],
        }
        assert [int(row[0]) for row in rows] == list(range(1, len(rows)+1))
        assert [int(row[1]) for row in rows] == expected_percentages[code]
        assert sum(int(row[1]) for row in rows) == 100
        assert rows[-1][2] == 'Không có ràng buộc bổ sung'
        actual = {}
        for directory, suffix in [('in', 'in'), ('out', 'out')]:
            for file in (p / directory).glob('*.' + suffix):
                actual[file.name] = hashlib.sha256(file.read_bytes()).hexdigest()
        assert actual == json.loads((p / 'hash.json').read_text()), code
        # Check the checker accepts correct answers and rejects corrupt output.
        sample = p / 'in/example_00.in'
        jury = p / 'out/example_00.out'
        tokens = jury.read_text().split()
        with tempfile.TemporaryDirectory() as tmp:
            candidate = Path(tmp) / 'candidate.out'
            for accept, content in [
                (True, jury.read_text()),
                (True, ' \n' + '\t'.join(tokens) + '\n'),
                (False, str(int(tokens[0]) + 1) + ' ' + ' '.join(tokens[1:])),
                (False, ' '.join(tokens[:-1])),
                (False, jury.read_text() + ' 0\n'),
                (False, 'not-an-integer\n'),
            ]:
                candidate.write_text(content)
                result = subprocess.run([str(p / 'checker'), str(sample), str(candidate), str(jury)],
                                        capture_output=True, timeout=5)
                assert (result.returncode == 0) == accept, (code, content, result.stderr)
        print('PASS:', code, 'statement, samples, hashes, checker corruption tests', flush=True)
    invalid = {
        'matha3': ['0 1 1\n1 1\n', '1 1 1\n2 1\n', '1 1 1\n1 1000000000000000001\n'],
        'stringa3': ['0\n1\n', '2\na-b\n', '2\n\n', '2\n' + '1'*100001 + '\n'],
        'bs13c': ['1 1\n0\n1\n', '1 1\n1\n1000000001\n'],
        'dpupstair03c': ['3 2 1\n2 2\n', '3 1 1\n4\n', '3 0 31\n\n'],
        'bs52c': ['2 1\n1 2\n1\n', '3 1\n1 2 3\n2\n', '3 1\n1 2 3\n0\n'],
    }
    for code, cases in invalid.items():
        for data in cases:
            result = subprocess.run([str(ROOT / 'custom' / code / 'verifier')], input=data,
                                    text=True, capture_output=True, timeout=5)
            assert result.returncode != 0, (code, data)
        # Valid input followed by an extra token must fail, too.
        data = (ROOT / 'custom' / code / 'gen/example_00.in').read_text() + '0\n'
        result = subprocess.run([str(ROOT / 'custom' / code / 'verifier')], input=data,
                                text=True, capture_output=True, timeout=5)
        assert result.returncode != 0, code
    print('PASS: invalid input rejected by all verifiers', flush=True)


def check_subtask_inputs():
    groups = {'matha3': 2, 'stringa3': 2, 'bs13c': 1, 'dpupstair03c': 2}
    checked = 0
    for code, count in groups.items():
        for sub in range(1, count+1):
            files = sorted((ROOT / 'custom' / code / 'in').glob(f'subtask{sub}_*.in'))
            assert len(files) == GROUP_COUNTS[code][sub-1], (code, sub, len(files))
            for file in files:
                data = file.read_text().split()
                if code == 'matha3':
                    a, _, q = map(int, data[:3])
                    if sub == 1:
                        assert q == 1 and max(map(int, data[3:])) <= 10**6
                    else:
                        assert a == 1
                elif code == 'stringa3':
                    k, text = int(data[0]), data[1]
                    if sub == 1:
                        assert k == 1
                    else:
                        value = 0
                        for char in text:
                            if '0' <= char <= '9':
                                value = value*10 + int(char)
                                assert value <= 10**12, file
                            else:
                                value = 0
                elif code == 'bs13c':
                    n, q = map(int, data[:2])
                    assert n*q <= 10**6
                else:
                    n, _, m = map(int, data[:3])
                    assert (n <= 20 if sub == 1 else m == 0)
                checked += 1
    print('PASS:', checked, 'dedicated subtask tests satisfy their constraints', flush=True)


def brute_math():
    for a in range(1, 7):
        for b in range(1, 7):
            queries = [(l, r) for l in range(1, 26) for r in range(l, 26)]
            data = f'{a} {b} {len(queries)}\n' + ''.join(f'{l} {r}\n' for l, r in queries)
            expected = [sum((x-1) % (a+b) < a for x in range(l, r+1)) for l, r in queries]
            compare('matha3', data, expected)


def brute_string():
    fixed = ['0', 'A', '9', '12a34', '000a000', 'a001b001c', '9'*500,
             '0000000000000000000000000000000000000001a00002']
    for i in range(250):
        s = fixed[i] if i < len(fixed) else ''.join(RNG.choice('0123456789abAZ') for _ in range(RNG.randint(1, 500)))
        k = [1, 9, 10, 1000000000][i % 4] if i < 20 else RNG.randint(1, 10**9)
        total = sum(int(part) for part in re.findall('[0-9]+', s))
        compare('stringa3', f'{k}\n{s}\n', [total % k])


def brute_rooms():
    for _ in range(150):
        a = [RNG.randint(1, 30) for _ in range(RNG.randint(1, 40))]
        queries = list(range(1, 35)) + [10**9]
        data = f'{len(a)} {len(queries)}\n' + ' '.join(map(str, a)) + '\n' + ''.join(f'{x}\n' for x in queries)
        expected = []
        for x in queries:
            choices = [v-x for v in a if v >= x]
            if choices:
                best = min(choices)
                expected += [best, choices.count(best)]
            else:
                expected += [-1, 0]
        compare('bs13c', data, expected)


def brute_tiling():
    # Enumerate every possible set of disjoint adjacent pairs, without using DP.
    for n in range(1, 8):
        for blocked_mask in range(1 << n):
            blocked = {i+1 for i in range(n) if blocked_mask >> i & 1}
            valid_edges = [i for i in range(1, n) if i not in blocked and i+1 not in blocked]
            counts = [0] * (n//2 + 2)
            for mask in range(1 << len(valid_edges)):
                occupied = set()
                used = 0
                for j, left in enumerate(valid_edges):
                    if mask >> j & 1:
                        if left in occupied or left+1 in occupied:
                            break
                        occupied.update((left, left+1))
                        used += 1
                else:
                    counts[used] += 1
            for m in range(n//2 + 2):
                data = f'{n} {len(blocked)} {m}\n' + ' '.join(map(str, sorted(blocked, reverse=True))) + '\n'
                compare('dpupstair03c', data, [counts[m]])


def brute_median():
    for _ in range(200):
        a = [RNG.randint(-5, 5) for _ in range(RNG.randint(3, 14))]
        values = sorted(sorted(triple)[1] for triple in combinations(a, 3))
        queries = list(range(1, len(values)+1))
        RNG.shuffle(queries)
        data = f'{len(a)} {len(queries)}\n' + ' '.join(map(str, a)) + '\n' + ''.join(f'{k}\n' for k in queries)
        compare('bs52c', data, [values[k-1] for k in queries])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build', action='store_true', help='Regenerate and validate all tests first; never export HTML')
    parser.add_argument('--update-hashes', action='store_true', help='Accept intentionally regenerated test hashes; requires --build')
    args = parser.parse_args()
    if args.update_hashes and not args.build:
        parser.error('--update-hashes requires --build')
    logging.basicConfig(level=logging.WARNING)
    if args.build:
        build(update_hashes=args.update_hashes)
    check_artifacts()
    check_subtask_inputs()
    check_scoring_files()
    for routine in (brute_math, brute_string, brute_rooms, brute_tiling, brute_median):
        routine()
        print('PASS:', routine.__name__, flush=True)
    print('Independent brute-force cases per task:', COUNTS)
    print('ALL CHECKS PASSED')


if __name__ == '__main__':
    main()
