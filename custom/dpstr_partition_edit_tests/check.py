"""Build and verify the 20 partition and edit problems."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import logging
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path[:0] = [str(HERE), str(ROOT)]
from oracle import answer
from problem import Problem
from problem_upload import ProblemUpload

CODES = [400, 401, 402, 403, 430, 431, 432, 450, 451, 452,
         500, 501, 502, 503, 530, 531, 532, 550, 551, 552]
NAMES = [f"dpstr{code}" for code in CODES]
UPLOAD = dict(time_limit=1.0, memory_limit=131072, group="03", classes="C", types=["dp_string"],
              allowed_languages=["PY3", "CPP11", "CPP14", "CPP17", "CPP20", "JAVA8", "C", "PAS"],
              partial=True)


def compile_source(path):
    standard = "c++11" if path.parent.name == "sol" else "c++17"
    subprocess.run(["g++", "-O2", f"-std={standard}", "-Wall", "-Wextra", "-Werror",
                    "-Wno-unused-result", "-I", str(ROOT / "common"),
                    str(path), "-o", str(path.with_suffix(""))], check=True)


def run(command, data=None, timeout=10):
    result = subprocess.run([str(part) for part in command], input=data, text=True,
                            capture_output=True, timeout=timeout)
    assert result.returncode == 0, (command, result.stderr)
    return result.stdout


def audit_statement(problem, code):
    folder = problem.basedir
    task = (folder / "task.md").read_text()
    headings = re.findall(r"^#{1,6} .+$", task, re.M)
    assert headings[0].startswith(f"# DPSTR{code} — ")
    assert headings[1:] == [
        "### Đề bài", "### Dữ liệu vào", "### Dữ liệu ra", "### Ràng buộc",
        "### Sample Input 1", "### Sample Output 1", "### Sample Input 2",
        "### Sample Output 2", "### Giải thích",
    ], (folder, headings)
    blocks = re.findall(r"```text\n(.*?)\n```", task, re.S)
    assert len(blocks) == 4
    for i in range(2):
        data = blocks[2 * i] + "\n"
        assert data == (folder / "gen" / f"example_{i:02}.in").read_text()
        assert answer(code, data) == blocks[2 * i + 1], (folder, i)
    solution = (folder / "solution.md").read_text()
    assert not re.search(r"^# |kiểm thử|bộ sinh|oracle|verifier|checker|benchmark", solution, re.M | re.I)
    for source in (task, solution):
        assert all(line.count("$") % 2 == 0 for line in source.splitlines())
        assert not any(ord(ch) < 32 and ch not in "\n\t" for ch in source)


def audit_config(problem, code):
    config = problem.config
    assert config["timelimit"] == 1.0 and isinstance(config["timelimit"], float)
    assert config["upload"] == UPLOAD
    assert isinstance(config["upload"]["time_limit"], float)
    metadata = ProblemUpload(problem)
    assert metadata.code == f"dpstr{code}"
    assert metadata.manifest["checker"] == "standard"
    assert config["tests"] == [{"name": "example.in", "number": 2}, {"name": "data.cpp", "number": 30}]
    n, m = config["params"]["N_MAX"], config["params"]["M_MAX"]
    if code == 550:
        work = 3 * n * m
    elif code == 551:
        work = 101 * (n + 1) + m
    elif code == 451:
        work = n * (n + 1)
    elif code == 450:
        work = 101 * n * (n + 1) // 2
    elif code == 452:
        work = 3 * n * (n + 1).bit_length()
    elif code == 431:
        work = 100 * (n + 5000)
    elif code == 430:
        work = 100 * n + 26 * 50000
    elif code < 500 or code == 502:
        work = 50 * n
    else:
        work = n * m
    assert work <= 50_000_000, (code, work)
    assert not list(problem.basedir.glob("*.html"))


def audit_verifier(folder, code, sample):
    lines = sample.splitlines()
    tokens = lines[0].split()
    invalid = ["", sample + "0\n", "\n".join(lines[:-1]) + "\n"]
    invalid += [" ".join([str(n), *tokens[1:]]) + "\n" + "\n".join(lines[1:]) + "\n"
                for n in (0, len(lines[1]) + 1)]
    invalid.append("\n".join([lines[0], "#" + lines[1][1:], *lines[2:]]) + "\n")
    if code == 530:
        invalid.append("\n".join([lines[0], "?" + lines[1][1:], *lines[2:]]) + "\n")
    if code in (431, 450, 551):
        index = 2 if code == 551 else 1
        bad = tokens.copy()
        bad[index] = "101"
        invalid.append("\n".join([" ".join(bad), *lines[1:]]) + "\n")
    for data in invalid:
        result = subprocess.run([str(folder / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (folder, "verifier accepted", data)


def audit_checker(folder, sample, expected):
    tokens = expected.split()
    wrong = tokens.copy()
    wrong[-1] = str(int(wrong[-1]) + 1)
    with tempfile.TemporaryDirectory() as temp:
        inp, out, ans = [Path(temp) / name for name in ("input", "output", "answer")]
        inp.write_text(sample)
        ans.write_text(expected + "\n")
        variants = [(expected + "\n", True), ("  " + expected + " \n", True),
                    (" ".join(wrong) + "\n", False), (expected + " 0\n", False),
                    ("", False), ("x\n", False)]
        if len(tokens) > 1:
            variants.append((" ".join(tokens[:-1]) + "\n", False))
        for content, accepted in variants:
            out.write_text(content)
            result = subprocess.run([str(folder / "checker"), str(inp), str(out), str(ans)],
                                    capture_output=True)
            assert (result.returncode == 0) == accepted, (folder, content, result.stderr)


def audit_cases(problem, code, update_hashes):
    folder = problem.basedir
    problem.make_inputs()
    problem.verify_inputs()
    problem.make_outputs(True)
    assert problem.check_all_solutions_used()
    paths = sorted((folder / "in").glob("*.in"))
    assert len(paths) == 32
    slowest = (0.0, "")
    for path in paths:
        data = path.read_text()
        official = (folder / "out" / path.with_suffix(".out").name).read_text().strip()
        start = time.perf_counter()
        actual = run([folder / "sol" / "correct"], data, timeout=problem.config["timelimit"]).strip()
        slowest = max(slowest, (time.perf_counter() - start, path.name))
        assert actual == official, path
        if path.stem.startswith("data_"):
            seed = int(path.stem[5:])
            assert run([folder / "gen" / "data", seed]) == data, path
            maximum_seed = seed - 26 if seed >= 26 else None
            if seed == 26:
                tokens = list(map(int, data.splitlines()[0].split()))
                params = problem.config["params"]
                assert tokens[0] == params["N_MAX"], path
                if params["M_MAX"]:
                    assert tokens[1] == params["M_MAX"], path
        else:
            maximum_seed = None
        expected = answer(code, data, maximum_seed)
        assert expected == official, (path, expected, official)
    sample = (folder / "in" / "example_00.in").read_text()
    audit_verifier(folder, code, sample)
    audit_checker(folder, sample, answer(code, sample))
    if update_hashes:
        (folder / "hash.json").write_text(json.dumps(problem.calc_hashes(), indent=2, sort_keys=True) + "\n")
    problem.assert_hashes()
    assert len(problem.calc_hashes()) == 64
    print(f"{folder.name}: 32 pairs verified, worst {slowest[0]:.3f}s ({slowest[1]}).", flush=True)
    return folder.name, slowest[0], slowest[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    problems = [Problem(ROOT, ROOT / "custom" / name) for name in args.problem]
    sources = []
    for problem in problems:
        code = int(problem.basedir.name[5:])
        problem.health_check()
        problem.generate_params_h()
        audit_statement(problem, code)
        audit_config(problem, code)
        sources.extend([problem.get_correct_filename(), problem.checker, problem.verifier, problem.basedir / "gen" / "data.cpp"])
    print(f"Compiling {len(sources)} sources...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(compile_source, sources))
    report = [audit_cases(problem, int(problem.basedir.name[5:]), args.update_hashes)
              for problem in problems]
    lines = ["# Kết quả kiểm tra nhóm 5 và nhóm 6", "",
             "Lời giải C++11 được chạy với giới hạn 1 giây mỗi test trên máy cục bộ.", "",
             "| Mã | Cặp input/output | Thời gian chậm nhất (giây) | Test |",
             "| --- | --- | --- | --- |"]
    lines.extend(f"| {name} | 32 | {time_taken:.4f} | {test} |" for name, time_taken, test in report)
    lines.extend(["", f"Tổng cộng {32 * len(report)} cặp test đạt đối chiếu đáp án và mã băm."])
    target = HERE / "results.md" if len(report) == 20 else problems[0].basedir / "tests" / "results.md"
    target.write_text("\n".join(lines) + "\n")
    print("All checks passed.", flush=True)


if __name__ == "__main__":
    main()
