"""Generate and verify the four DTVICTOR problems without exporting HTML."""

import argparse
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
from tempfile import TemporaryDirectory
from time import perf_counter

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT))

from problem import Problem, casename, execcmd
from problem_upload import ProblemUpload

CODES = [f"dtvictor{i}" for i in range(1, 5)]


def build(source, target):
    flags = os.environ.get("CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror")
    subprocess.run(
        [os.environ.get("CXX", "g++"), *shlex.split(flags), "-I", str(ROOT / "common"),
         str(source), "-o", str(target)],
        check=True,
    )


def run(command, data=b"", timeout=20, check=True):
    return subprocess.run(
        list(map(str, command)), input=data, capture_output=True, timeout=timeout, check=check
    )


def audit(problem):
    folder = problem.basedir
    task = (folder / "task.md").read_text()
    solution = (folder / "solution.md").read_text()
    title = task.splitlines()[0]
    assert title.startswith(f"# {folder.name.upper()} — ")
    assert problem.config["title"] == title[2:]
    headings = [title, "### Đề bài", "### Dữ liệu vào", "### Dữ liệu ra",
                "### Ràng buộc"]
    for i in (1, 2):
        headings.extend([f"### Sample Input {i}", f"### Sample Output {i}"])
    headings.extend(["### Giải thích", "### Nguồn"])
    assert re.findall(r"^#+ .+$", task, re.M) == headings
    assert not re.search(r"^# |kiểm thử|kiểm chứng|bộ sinh|oracle|verifier|checker|benchmark",
                         solution, re.M | re.I)
    assert problem.config["timelimit"] == problem.config["upload"]["time_limit"] == 1.0
    assert problem.check_all_solutions_used()
    upload = ProblemUpload(problem)
    assert upload.payload["points"] == 100
    assert len(upload.manifest["cases"]) == sum(t["number"] for t in problem.config["tests"])

    samples = {}
    for i in (1, 2):
        name = f"example_{i - 1:02}"
        for label in ("Input", "Output"):
            match = re.search(rf"### Sample {label} {i}\n\n```text\n(.*?)```", task, re.S)
            assert match, f"{folder.name}: invalid sample {i} {label}"
            if label == "Input":
                assert match[1] == (folder / "gen" / f"{name}.in").read_text()
            else:
                samples[name] = match[1].encode()
    return samples


def small_cases(static):
    rng = random.Random(20201105)
    for i in range(120):
        n = rng.randint(1, 40)
        k = rng.randint(1, n)
        m = rng.randint(1, 90)
        labels = list(range(2, n + 1))
        rng.shuffle(labels)
        labels = [0, 1] + labels
        roads = []
        for u in range(2, n + 1):
            p = rng.choice((1, u - 1, rng.randint(1, u - 1)))
            a, b = labels[u], labels[p]
            roads.append((a, b) if rng.randrange(2) else (b, a))
        rng.shuffle(roads)
        guards = [rng.randint(1, k) for _ in range(n)]
        lines = [f"{n} {k} {m}", " ".join(map(str, guards))]
        lines.extend(f"{u} {v}" for u, v in roads)
        for j in range(m):
            u = rng.randint(1, n)
            if not static and (i % 10 == 0 or rng.randrange(3)):
                guard = guards[u - 1] if j % 7 == 0 else rng.randint(1, k)
                lines.append(f"1 {u} {guard}")
                guards[u - 1] = guard
            else:
                lines.append(f"2 {u}")
        yield ("\n".join(lines) + "\n").encode()


def check_invalid(verifier, params):
    rejected = [
        f'{params["N_MAX"] + 1} 1 1\n',
        f'1 1 {params["M_MAX"] + 1}\n',
        "0 1 1\n",
        "1 2 1\n",
        "1 1 1\n2\n2 1\n",
        "2 1 1\n1 1\n1 1\n2 1\n",
        "3 1 1\n1 1 1\n1 2\n2 1\n2 1\n",
        "3 1 1\n1 1 1\n1 2\n2 4\n2 1\n",
        "1 1 1\n1\n3 1\n",
        "1 1 1\n1\n2 2\n",
        "1 1 2\n1\n2 1\n",
        "1 1 1\n1\n2 1\n2 1\n",
    ]
    update = "1 1 1\n1\n1 1 1\n"
    if params["STATIC_GUARDS"]:
        rejected.append(update)
    else:
        run(verifier, update.encode())
        rejected.extend(["1 1 1\n1\n1 1 2\n", "1 1 1\n1\n1 1\n"])
    for data in rejected:
        assert run(verifier, data.encode(), check=False).returncode != 0, data
    return len(rejected)


def check_checker(checker, folder, scratch):
    infile = folder / "in" / "example_00.in"
    answer = folder / "out" / "example_00.out"
    tokens = answer.read_bytes().split()
    candidate = scratch / "candidate.out"
    outputs = [
        (b" \n".join(tokens) + b"\n", True),
        (b"0 " + b" ".join(tokens[1:]), False),
        (b" ".join(tokens[:-1]), False),
        (answer.read_bytes() + b"9\n", False),
        (b"x " + b" ".join(tokens[1:]), False),
        (b"2147483648 " + b" ".join(tokens[1:]), False),
    ]
    for content, accepted in outputs:
        candidate.write_bytes(content)
        result = run([*checker, infile, candidate, answer], check=False)
        assert (result.returncode == 0) == accepted, (content, result.stderr)
    empty_case = folder / "out" / "cases_20.out"
    if empty_case.stat().st_size == 0:
        candidate.write_bytes(b"1\n")
        infile = folder / "in" / "cases_20.in"
        result = run([*checker, infile, candidate, empty_case], check=False)
        assert result.returncode != 0
        return len(outputs) + 1
    return len(outputs)


def check_problem(code, oracle, scratch, update_hashes):
    folder = HERE.parent / code
    problem = Problem(ROOT, folder)
    problem.health_check()
    problem.generate_params_h()
    sources = [problem.get_correct_filename(), problem.verifier, problem.checker,
               folder / "gen" / "cases.cpp"]
    for source in sources:
        build(source, Path(execcmd(source)[0]))
    problem.clean()
    problem.make_inputs()
    samples = audit(problem)
    verifier, checker = execcmd(problem.verifier), execcmd(problem.checker)
    solution = execcmd(problem.get_correct_filename())
    limit = problem.config["timelimit"]

    outdir = folder / "out"
    outdir.mkdir()
    peak = (0.0, "")
    cases = 0
    for group in problem.config["tests"]:
        generator = folder / "gen" / group["name"]
        for i in range(group["number"]):
            name = casename(generator, i)
            infile = folder / "in" / f"{name}.in"
            data = infile.read_bytes()
            assert run(execcmd(generator, [str(i)])).stdout == data, (code, name)
            run(verifier, data)
            expected = run([oracle], data).stdout
            output = outdir / f"{name}.out"
            start = perf_counter()
            try:
                problem.run_solution(problem.get_correct_filename(), infile, output, timeout=limit)
            except subprocess.TimeoutExpired as error:
                raise RuntimeError(f"{code}/{name}: exceeded {limit:.1f} s") from error
            peak = max(peak, (perf_counter() - start, name))
            actual = output.read_bytes()
            assert actual == expected, (code, name)
            if name in samples:
                assert actual == samples[name], (code, name)

            reference = scratch / "oracle.out"
            reference.write_bytes(expected)
            run([*checker, infile, output, reference])
            cases += 1

    params = problem.config["params"]
    for data in small_cases(params["STATIC_GUARDS"]):
        run(verifier, data)
        assert run(solution, data, timeout=limit).stdout == run([oracle], data).stdout, (code, data)
    rejected = check_invalid(verifier, params)
    checker_cases = check_checker(checker, folder, scratch)

    if update_hashes:
        problem.ignore_warning = True
        problem.write_hashes()
    problem.assert_hashes()
    print(f"{code.upper()}: {cases} official, 120 small, {rejected} invalid inputs, "
          f"{checker_cases} checker cases, max {peak[0]:.3f}/{limit:.1f} s ({peak[1]})", flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", choices=CODES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    with TemporaryDirectory() as scratch:
        scratch = Path(scratch)
        oracle = scratch / "oracle"
        build(HERE / "oracle.cpp", oracle)
        for code in [args.problem] if args.problem else CODES:
            check_problem(code, oracle, scratch, args.update_hashes)


if __name__ == "__main__":
    main()
