"""Đối chiếu lời giải với vét cạn và kiểm tra bộ dữ liệu đã sinh."""

import itertools
import logging
import random
import re
import subprocess
import sys
from pathlib import Path
from tempfile import TemporaryDirectory

PACKAGE = Path(__file__).resolve().parents[1]
ROOT = PACKAGE.parents[1]
sys.path.insert(0, str(ROOT))

from problem import Problem, casename
from problem_upload import ProblemUpload


def regenerate(problem):
    problem.health_check()
    problem.generate_params_h()
    problem.compile_correct()
    problem.compile_gens()
    problem.compile_verifier()
    problem.compile_checker()
    problem.make_inputs()
    problem.verify_inputs()
    problem.make_outputs(check=True)


def solve(toys):
    data = str(len(toys)) + "\n" + "".join(f"{c} {s}\n" for c, s in toys)
    return int(subprocess.check_output([PACKAGE / "sol/correct"], input=data.encode(), timeout=1))


def brute(toys):
    n = len(toys)
    best = float("inf")
    for mask in range(1, (1 << n) - 1):
        colors = [c for i, (c, _) in enumerate(toys) if mask >> i & 1]
        sizes = [s for i, (_, s) in enumerate(toys) if not (mask >> i & 1)]
        best = min(best, max(colors) - min(colors) + max(sizes) - min(sizes))
    return best


def quadratic(toys):
    toys.sort()
    n = len(toys)
    best = float("inf")
    prefix_min, prefix_max = float("inf"), -float("inf")
    for l, (left_color, left_size) in enumerate(toys):
        bob_min, bob_max = prefix_min, prefix_max
        for r in range(n - 1, l - 1, -1):
            color, size = toys[r]
            if l > 0 or r < n - 1:
                best = min(best, color - left_color + bob_max - bob_min)
            bob_min = min(bob_min, size)
            bob_max = max(bob_max, size)
        prefix_min = min(prefix_min, left_size)
        prefix_max = max(prefix_max, left_size)
    return best


def check_oracle():
    samples = [
        ([(0, 0), (5, 5), (1, 1), (3, 4)], 2),
        ([(0, 2), (5, 0), (5, 9), (10, 2)], 0),
        ([(0, 0), (100000000, 100000000)], 0),
        ([(100000000, 41), (50000000, 0), (0, 40), (50000001, 100000000)], 2),
    ]
    for toys, expected in samples:
        assert brute(toys) == expected
        assert solve(toys) == expected, toys

    grid = list(itertools.product(range(3), repeat=2))
    rng = random.Random(134928)
    cases = itertools.chain(
        *(itertools.combinations_with_replacement(grid, n) for n in range(2, 5)),
        ([rng.choice(grid) for _ in range(rng.randint(5, 10))] for _ in range(250)),
    )
    count = len(samples)
    for toys in cases:
        toys = list(toys)
        rng.shuffle(toys)
        expected = brute(toys)
        assert solve(toys) == expected, (toys, expected)
        count += 1
    print(f"{count} trường hợp khớp vét cạn mọi cách chia")


def check_package(problem):
    upload = ProblemUpload(problem)
    limits = [20, 200, 2000, 50000, 500000, 2000000]
    weights = [10, 20, 20, 20, 20, 10]
    groups = []
    current = None
    files = []
    for row in upload.manifest["cases"]:
        if row.get("type") == "S":
            assert current is None
            current = (row["points"], [])
        elif row.get("type") == "E":
            assert current is not None
            groups.append(current)
            current = None
        else:
            files.append(row["input_file"])
            with (PACKAGE / "in" / row["input_file"]).open() as source:
                n = int(source.readline())
            assert row["output_file"] == row["input_file"].replace(".in", ".out")
            if current is not None:
                current[1].append(n)
            else:
                assert row["points"] == 0
                assert row["is_pretest"]

    assert current is None
    assert [weight for weight, _ in groups] == weights
    assert [max(sizes) for _, sizes in groups] == limits
    assert sorted(files) == sorted(case + ".in" for case in upload.cases)
    assert problem.config["timelimit"] == problem.config["upload"]["time_limit"] == 1.0
    assert problem.config["upload"]["memory_limit"] == 65536

    for index in range(9):
        case = casename("cases.cpp", index)
        rows = (PACKAGE / "in" / f"{case}.in").read_text().splitlines()
        toys = [tuple(map(int, row.split())) for row in rows[1:]]
        expected = quadratic(toys)
        assert int((PACKAGE / "out" / f"{case}.out").read_text()) == expected, case
    for index, expected in {11: 0, 13: 2, 17: 2}.items():
        case = casename("cases.cpp", index)
        assert int((PACKAGE / "out" / f"{case}.out").read_text()) == expected, case

    statement = (PACKAGE / "task.md").read_text()
    assert statement.splitlines()[0] == f"# {problem.config['title']}"
    headings = re.findall(r"^### (.+)$", statement, re.M)
    assert headings == [
        "Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc", "Subtask",
        "Sample Input 1", "Sample Output 1", "Sample Input 2", "Sample Output 2", "Giải thích",
    ]
    for sample in range(2):
        for heading, folder, ext in (("Input", "in", "in"), ("Output", "out", "out")):
            block = re.search(rf"### Sample {heading} {sample + 1}\n\n```text\n(.*?)```", statement, re.S)
            assert block.group(1) == (PACKAGE / folder / f"example_{sample:02}.{ext}").read_text()
    problem.assert_hashes()
    print("6 subtask, điểm, giới hạn, đáp án cố định và hash đều khớp")


def check_invalid_data():
    for data in (b"1\n0 0\n", b"2\n-1 0\n0 0\n", b"2\n0 0\n0 100000001\n", b"2\n0 0\n"):
        result = subprocess.run([PACKAGE / "verifier"], input=data, capture_output=True)
        assert result.returncode != 0, data

    with TemporaryDirectory() as directory:
        actual = Path(directory) / "actual.out"
        for output, expected_code in (("2\n", 0), ("3\n", 1), ("2 0\n", 1)):
            actual.write_text(output)
            result = subprocess.run([
                PACKAGE / "checker", PACKAGE / "in/example_00.in",
                actual, PACKAGE / "out/example_00.out",
            ], capture_output=True)
            assert result.returncode == expected_code, output
    print("Verifier và checker từ chối dữ liệu hoặc đáp án sai")


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    problem = Problem(ROOT, PACKAGE)
    regenerate(problem)
    check_oracle()
    check_package(problem)
    check_invalid_data()
