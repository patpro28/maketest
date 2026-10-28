"""Generate three tests for the wrong component-size comparator in rollback DSU."""
from pathlib import Path

HERE = Path(__file__).resolve().parent


def generate():
    results = []
    for seed, name in enumerate(["blue_chain", "mixed_large_pairs", "rollback_cycles"]):
        zero = 100000 if seed == 0 else 80000 if seed == 1 else 99500
        one = 40000 if seed == 1 else 1
        n, q = zero + one, 200000
        ops = [f"+ {v} {v-1}" for v in range(2, zero+1)]
        ops += [f"+ {v} {v-1}" for v in range(zero+2, n+1)]
        ops.append(f"+ {zero+1} {zero}")
        ops += [f"+ {v} 1" for v in range(3, zero+1)]
        if seed == 2:
            for v in range(3, 503):
                ops += [f"- 1 {v}", "?"]
            ops += [f"- {zero} {zero+1}", "?"]
        while len(ops) < q:
            ops.append("?")
        assert len(ops) == q
        data = f"{n} {q}\n" + " ".join(["0"]*zero + ["1"]*one) + "\n" + "\n".join(ops) + "\n"
        answers = [zero*one] * ops.count("?")
        if seed == 2:
            answers[-1] = 0
        path = HERE / f"{name}.in"
        path.write_text(data)
        path.with_suffix(".out").write_text("".join(f"{value}\n" for value in answers))
        results.append((path, answers))
    return results


if __name__ == "__main__":
    for path, answers in generate():
        print(f"{path.name}: {len(answers)} answers, first={answers[0]}, last={answers[-1]}")
