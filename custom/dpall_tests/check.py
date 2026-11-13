#!/usr/bin/env python3
"""Cross-check the generated DPALL answers with exhaustive small instances."""

import argparse
import re
import subprocess
import sys
import tomllib
from itertools import combinations
from pathlib import Path
from random import Random
from tempfile import TemporaryDirectory

CUSTOM = Path(__file__).resolve().parent.parent
MOD = 10**9 + 7


def regenerate(index):
    from problem import Problem

    problem = Problem(CUSTOM.parent, CUSTOM / f'dpall{index:04}')
    problem.health_check()
    problem.generate_params_h()
    problem.compile_correct()
    problem.compile_gens()
    problem.compile_verifier()
    problem.compile_checker()
    problem.make_inputs()
    problem.verify_inputs()
    problem.make_outputs(check=True)
    problem.assert_hashes()
    for solution in problem.config['solutions']:
        problem.judge(problem.basedir / 'sol' / solution['name'], solution)


def stair_costs(fees, max_jump, alternating):
    def visit(position, last, cost):
        if position == len(fees):
            yield cost
        for jump in range(1, max_jump + 1):
            landing = position + jump
            if landing <= len(fees) and (not alternating or jump != last):
                yield from visit(landing, jump, cost + fees[landing - 1])

    return list(visit(0, 0, 0))


def item_totals(target, items):
    def visit(index, remaining, value):
        if index == len(items):
            if remaining == 0:
                yield value
            return
        repeated, weight, points = items[index]
        limit = remaining // weight
        if not repeated:
            limit = min(limit, 1)
        for count in range(limit + 1):
            yield from visit(index + 1, remaining - count * weight, value + count * points)

    return list(visit(0, target, 0))


def shared_length(a, b):
    for length in range(min(len(a), len(b)), -1, -1):
        if set(combinations(a, length)) & set(combinations(b, length)):
            return length


def monotone_grid_cost(grid, turns):
    rows, cols = len(grid), len(grid[0])
    steps = rows + cols - 2
    costs = []
    for down in combinations(range(steps), rows - 1):
        directions = [step in down for step in range(steps)]
        if sum(a != b for a, b in zip(directions, directions[1:])) != turns:
            continue
        r = c = 0
        cells = [grid[0][0]]
        for vertical in directions:
            r += vertical
            c += not vertical
            cells.append(grid[r][c])
        if -1 not in cells:
            costs.append(sum(cells))
    return min(costs, default=-1)


def shared_score(a, b, cost_a, cost_b, points, budget):
    answer = -1
    for length in range(min(len(a), len(b)) + 1):
        for left in combinations(range(len(a)), length):
            word = tuple(a[i] for i in left)
            left_cost = sum(cost_a[i] for i in left)
            for right in combinations(range(len(b)), length):
                if left_cost + sum(cost_b[j] for j in right) != budget:
                    continue
                if word == tuple(b[j] for j in right):
                    answer = max(answer, sum(points[ord(ch) - ord('a')] for ch in word))
    return answer


def free_intervals(m, forbidden):
    return sum(not any(left <= start <= end <= right for start, end in forbidden)
               for left in range(1, m + 1) for right in range(left, m + 1))


def reversed_score(word, scores):
    def score(candidate):
        return sum(scores[a][b] for a, b in zip(candidate, candidate[1:]))

    return max(score(word[:left] + word[left:right][::-1] + word[right:])
               for left in range(len(word)) for right in range(left + 1, len(word) + 1))


def simple_grid_path(grid):
    rows, cols = len(grid), len(grid[0])
    answer = -10**30
    seen = set()

    def visit(r, c, total):
        nonlocal answer
        total += grid[r][c]
        if r == rows - 1:
            answer = max(answer, total)
        seen.add((r, c))
        for i, j in ((r + 1, c), (r, c - 1), (r, c + 1)):
            if i < rows and 0 <= j < cols and (i, j) not in seen:
                visit(i, j, total)
        seen.remove((r, c))

    for c in range(cols):
        visit(0, c, 0)
    return answer


def solve_small(index, data):
    lines = data.splitlines()
    header = list(map(int, lines[0].split()))
    if index in (0, 3):
        fees = list(map(int, lines[1].split()))
        costs = stair_costs(fees, 2 if index == 0 else 3, alternating=index == 3)
        best = min(costs)
        return (best,) if index == 0 else (best, costs.count(best) % MOD)
    if index in (1, 5):
        items = [tuple(map(int, line.split())) for line in lines[1:]]
        if index == 1:
            items = [(0, weight, value) for weight, value in items]
        values = item_totals(header[1], items)
        best = max(values, default=-1)
        return (best,) if index == 1 else (best, values.count(best) % MOD)
    if index == 2:
        return (shared_length(*lines[1:]),)
    if index == 4:
        grid = [list(map(int, line.split())) for line in lines[1:]]
        return (monotone_grid_cost(grid, header[2]),)
    if index == 6:
        cost_a, cost_b, points = [list(map(int, line.split())) for line in lines[3:]]
        return (shared_score(lines[1], lines[2], cost_a, cost_b, points, header[2]),)
    if index == 7:
        forbidden = [tuple(map(int, line.split())) for line in lines[1:]]
        return (free_intervals(header[1], forbidden),)
    if index == 8:
        word = [ord(ch) - ord('A') for ch in lines[1]]
        return (reversed_score(word, [list(map(int, line.split())) for line in lines[2:]]),)
    grid = [list(map(int, line.split())) for line in lines[1:]]
    return (simple_grid_path(grid),)


def make_small(index, rng):
    def numbers(count, low, high):
        return ' '.join(str(rng.randint(low, high)) for _ in range(count))

    def word(count):
        return ''.join(rng.choice('abc') for _ in range(count))

    n = rng.randint(1, 10)
    if index in (0, 3):
        return [str(n), numbers(n, 0, 7)]
    if index in (1, 5):
        n = min(n, 6) if index == 5 else n
        lines = [f'{n} {rng.randint(0, 15)}']
        for _ in range(n):
            item = f'{rng.randint(1, 8)} {rng.randint(0, 8)}'
            lines.append(f'{rng.randrange(2)} {item}' if index == 5 else item)
        return lines
    if index in (2, 6):
        n = min(n, 7) if index == 6 else n
        m = rng.randint(1, 7)
        header = f'{n} {m}'
        a, b = word(n), word(m)
        if index == 2:
            return [header, a, b]
        return [f'{header} {rng.randint(0, 20)}', a, b,
                numbers(n, 1, 5), numbers(m, 1, 5), numbers(26, 0, 10)]
    if index in (4, 9):
        rows, cols = rng.randint(1, 4), rng.randint(1, 5)
        header = f'{rows} {cols}'
        if index == 4:
            header += f' {rng.randint(0, rows + cols)}'
            return [header] + [numbers(cols, -1, 5) for _ in range(rows)]
        return [header] + [numbers(cols, -8, 8) for _ in range(rows)]
    if index == 7:
        m = rng.randint(1, 18)
        intervals = [sorted((rng.randint(1, m), rng.randint(1, m))) for _ in range(n)]
        return [f'{n} {m}'] + [f'{left} {right}' for left, right in intervals]
    return [str(n), word(n).upper()] + [numbers(3, -9, 9) for _ in range(3)]


def check_problem(index, rng):
    base = CUSTOM / f'dpall{index:04}'
    task = (base / 'task.md').read_text(encoding='utf-8')
    with (base / 'info.toml').open('rb') as stream:
        config = tomllib.load(stream)
    timeout = config['timelimit']
    assert timeout == config['upload']['time_limit'] == 1.0, base
    assert config['upload']['types'] == ['dp_all'], base
    headings = [line for line in task.splitlines() if line.startswith('#')]
    assert config['title'].startswith(base.name.upper() + ' — '), base
    assert headings == [
        f"# {config['title']}", '### Đề bài', '### Dữ liệu vào', '### Dữ liệu ra', '### Ràng buộc',
        '### Sample Input 1', '### Sample Output 1', '### Sample Input 2',
        '### Sample Output 2', '### Giải thích',
    ], base
    assert not re.search(r'^# ', (base / 'solution.md').read_text(encoding='utf-8'), re.M), base

    fence = '```'
    examples = re.findall(rf'^### Sample (Input|Output) ([12])\n\n{fence}text\n(.*?)\n{fence}',
                          task, re.M | re.S)
    assert len(examples) == 4, base
    for direction, number, body in examples:
        stem = f'example_{int(number) - 1:02}'
        file = (base / 'gen' / f'{stem}.in' if direction == 'Input'
                else base / 'out' / f'{stem}.out')
        assert file.read_text() == body + '\n', (base, file.name)

    small_paths = (sorted((base / 'in').glob('example_*.in'))
                   + sorted((base / 'in').glob('edge_*.in'))
                   + [base / 'in' / f'random_{i:02}.in' for i in range(8)])
    for path in small_paths:
        expected = solve_small(index, path.read_text())
        actual = tuple(map(int, (base / 'out' / f'{path.stem}.out').read_text().split()))
        assert actual == expected, (path, actual, expected)

    for case in range(60):
        data = '\n'.join(make_small(index, rng)) + '\n'
        expected = solve_small(index, data)
        result = subprocess.run([base / 'sol' / 'correct'], input=data, capture_output=True,
                                check=True, text=True, timeout=timeout)
        actual = tuple(map(int, result.stdout.split()))
        assert actual == expected, (base, case, actual, expected, data)

    with TemporaryDirectory() as directory:
        output = Path(directory) / 'submission.out'
        sample = base / 'in' / 'example_00.in'
        answer = base / 'out' / 'example_00.out'
        original = answer.read_text()
        first, *rest = original.split()
        wrong = ' '.join([str(int(first) + 1), *rest]) + '\n'
        for invalid in (wrong, original + '0\n', ''):
            output.write_text(invalid)
            result = subprocess.run([base / 'checker', sample, output, answer], capture_output=True)
            assert result.returncode != 0, (base, invalid)
        invalid_input = sample.read_bytes() + b'0\n'
        result = subprocess.run([base / 'verifier'], input=invalid_input, capture_output=True)
        assert result.returncode != 0, base

    print(f'{base.name}: {len(small_paths)} generated and 60 fresh cases matched', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--regenerate', action='store_true',
                        help='rebuild, verify, and judge official tests before checking small cases')
    args = parser.parse_args()
    if args.regenerate:
        sys.path.insert(0, str(CUSTOM.parent))
    rng = Random(20261108)
    for index in range(10):
        if args.regenerate:
            regenerate(index)
        check_problem(index, rng)
