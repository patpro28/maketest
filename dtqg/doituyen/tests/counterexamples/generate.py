"""Generate valid tests that expose quadratic last-edge Dijkstra."""
from pathlib import Path

HERE = Path(__file__).resolve().parent
M = 200000
K = M // 2


def generate():
    cases = []
    for name, same_line in [("different_lines", False), ("same_line", True)]:
        inp = HERE / f"{name}.in"
        with inp.open("w") as f:
            f.write(f"3 {M} 1 3\n0 1000000000 0\n")
            for i in range(1, K + 1):
                f.write(f"1 2 {1 if same_line else i} 1\n")
            for i in range(K + 1, M + 1):
                f.write(f"2 3 {1 if same_line else i} 1\n")
        answer = 2 if same_line else 1000000002
        inp.with_suffix(".out").write_text(f"{answer}\n")
        cases.append((inp, answer))
    inp = HERE / "self_loops.in"
    with inp.open("w") as f:
        f.write(f"2 {M} 1 2\n0 0\n")
        for i in range(1, M):
            f.write(f"1 1 {i} 1\n")
        f.write("1 2 1000000000 1\n")
    inp.with_suffix(".out").write_text("1\n")
    cases.append((inp, 1))
    inp = HERE / "hub_self_loops.in"
    incoming = (M - 1) // 2
    with inp.open("w") as f:
        f.write(f"3 {M} 1 3\n0 1000000000 0\n")
        for i in range(1, incoming + 1):
            f.write(f"1 2 {i} 1\n")
        for i in range(incoming + 1, M):
            f.write(f"2 2 {i} 1\n")
        f.write("2 3 1000000000 1000000000\n")
    inp.with_suffix(".out").write_text("2000000001\n")
    cases.append((inp, 2000000001))
    return cases


if __name__ == "__main__":
    for inp, answer in generate():
        print(f"{inp.name}: answer = {answer}")
