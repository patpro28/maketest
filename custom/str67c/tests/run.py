#!/usr/bin/env python3
"""Generate and check STR67C without exporting HTML."""
import argparse
import itertools
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[3]
BASE = ROOT / "custom/str67c"
sys.path.insert(0, str(ROOT))
from problem import Problem  # noqa: E402


def run(exe, data):
    return subprocess.run([str(exe)], input=data, text=True, capture_output=True)


def expected_output(strings):
    # A good key occurs at a position different from both its neighbors.
    return "".join("".join(sorted({
        c for i, c in enumerate(s)
        if (i == 0 or s[i - 1] != c) and (i + 1 == len(s) or s[i + 1] != c)
    })) + "\n" for s in strings)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    if "CXX" not in os.environ and shutil.which("g++-16"):
        os.environ["CXX"] = shutil.which("g++-16")

    p = Problem(ROOT, BASE)
    p.health_check()
    p.generate_params_h()
    p.compile_correct()
    p.compile_gens()
    p.compile_verifier()
    p.compile_checker()
    p.make_inputs()
    p.verify_inputs()
    p.make_outputs(check=True)

    files = sorted((BASE / "in").glob("*.in"))
    total = 0
    for path in files:
        lines = path.read_text().splitlines()
        assert int(lines[0]) == len(lines) - 1
        answer = (BASE / "out" / (path.stem + ".out")).read_text()
        assert answer == expected_output(lines[1:]), path.name
        total += int(lines[0])
    assert (BASE / "out/example_00.out").read_text() == "a\nz\n\nbc\n"

    # Independently derive truth from key states and original presses.
    exhaustive = []
    for states in itertools.product((1, 2), repeat=3):
        for length in range(1, 8):
            for presses in itertools.product(range(3), repeat=length):
                if any(a == b for a, b in zip(presses, presses[1:])):
                    continue
                s = "".join(chr(97 + c) * states[c] for c in presses)
                truth = "".join(chr(97 + c) for c in sorted(set(presses)) if states[c] == 1)
                exhaustive.append((s, truth))
    for start in range(0, len(exhaustive), 100):
        batch = exhaustive[start:start + 100]
        data = str(len(batch)) + "\n" + "".join(s + "\n" for s, _ in batch)
        validation = run(BASE / "verifier", data)
        assert validation.returncode == 0, validation.stderr
        result = run(BASE / "sol/correct", data)
        assert result.returncode == 0, result.stderr
        assert result.stdout == "".join(truth + "\n" for _, truth in batch)

    invalid = [
        "0\n", "101\n" + "a\n" * 101, "1\n\n", "1\nA\n",
        "1\na1\n", "1\n" + "ab" * 250 + "a\n", "1\naaa\n",
        "1\nabaabb\n", "2\na\n", "1\na\nb\n", "1\na b\n",
    ]
    for data in invalid:
        assert run(BASE / "verifier", data).returncode != 0, repr(data)

    with tempfile.TemporaryDirectory(prefix="str67c-") as tmp:
        temp = Path(tmp)
        checked = 0

        def check(data, answer, actual, accepted):
            nonlocal checked
            paths = [temp / name for name in ("input", "answer", "actual")]
            for path, content in zip(paths, (data, answer, actual)):
                path.write_text(content)
            result = subprocess.run(
                [str(BASE / "checker"), str(paths[0]), str(paths[2]), str(paths[1])],
                capture_output=True, text=True,
            )
            assert (result.returncode == 0) == accepted, result.stderr
            checked += 1

        data = (BASE / "gen/example_00.in").read_text()
        answer = "a\nz\n\nbc\n"
        check(data, answer, answer, True)
        check(data, answer, "a\r\nz\r\n\r\nbc\r\n", True)
        check(data, answer, " a \n z\n \t\n bc \n", True)
        for bad in ("a\nz\nbc\n", "a\nz\nbc\n\n", "a\nz\n\ncb\n",
                    "a\nz\n\nbbc\n", "a\nz\n\nb c\n", answer + "a\n",
                    "", "a\nz\n\n", "a\nz\na\nbc\n"):
            check(data, answer, bad, False)
        check("1\naa\n", "\n", "\n", True)
        check("1\naa\n", "\n", "", False)
        check("2\naa\nbb\n", "\n\n", "\n\n", True)
        check("2\naa\nbb\n", "\n\n", "\n", False)
        check("2\na\nbb\n", "a\n\n", "a\n\n", True)
        check("2\na\nbb\n", "a\n\n", "a\n", False)

    task = (BASE / "task.md").read_text()
    assert task.splitlines()[0] == "# STR67C — Bàn phím bị hỏng"
    assert [line for line in task.splitlines() if line.startswith("### ")] == [
        "### Đề bài", "### Dữ liệu vào", "### Dữ liệu ra", "### Ràng buộc",
        "### Sample Input 1", "### Sample Output 1", "### Giải thích",
    ]
    assert task.count("```text") == 2
    solution = (BASE / "solution.md").read_text()
    assert not any(line.startswith("# ") for line in solution.splitlines())
    reference = solution.split("```cpp\n")[1].split("```")[0]
    assert reference == (BASE / "sol/correct.cpp").read_text()
    if args.update_hashes:
        (BASE / "hash.json").write_text(json.dumps(p.calc_hashes(), indent=2, sort_keys=True) + "\n")
    p.assert_hashes()
    print(f"PASS: {len(files)} files, {total} generated cases, "
          f"{len(exhaustive)} exhaustive cases, {len(invalid)} invalid inputs, "
          f"{checked} checker checks; statement format and hashes match.")


if __name__ == "__main__":
    main()
