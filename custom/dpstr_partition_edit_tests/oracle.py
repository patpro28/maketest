"""Check small cases directly and maximum cases by their construction."""
from functools import lru_cache
from itertools import combinations
from math import comb

MOD = 1_000_000_007
INF = 10**30


def partition_answer(code, data):
    lines = data.splitlines()
    args = list(map(int, lines[0].split()))[1:]
    s = lines[1]
    n = len(s)
    words = {}
    if code == 430:
        for line in lines[2:]:
            word, cost = line.split()
            words[word] = min(words.get(word, INF), int(cost))

    if code == 451:
        @lru_cache(None)
        def increasing(start, previous):
            if start == n:
                return 1
            if s[start] == "0":
                return 0
            return sum(
                increasing(end, value)
                for end in range(start + 1, n + 1)
                if (value := int(s[start:end])) > previous
            ) % MOD

        return str(increasing(0, 0))

    exact = args[0] if code in (431, 450) else None

    def weight(piece):
        if code == 400:
            return 1 if piece in ("a", "ab", "ba", "bb") else None
        if code in (401, 402):
            low, high = args if code == 402 else (1, 26)
            return 1 if piece[0] != "0" and low <= int(piece) <= high else None
        if code == 403:
            return 1 if len(piece) <= args[0] and piece[0] == piece[-1] else None
        if code == 430:
            return words.get(piece)
        if code == 431:
            return 1 if sum(map(int, piece)) % args[1] == 0 else None
        if code == 432:
            low, high = args
            return 1 if low <= len(piece) <= high and len(piece) == len(set(piece)) else None
        if code == 450:
            return sum(x != y for x, y in zip(piece, reversed(piece))) // 2
        low, high, budget = args
        return 1 if low <= len(piece) <= high and sum(map(int, piece)) <= budget else None

    if n <= 12:
        costs = []
        choices = range(n) if exact is None else (exact - 1,)
        for cuts in choices:
            for mids in combinations(range(1, n), cuts):
                ends = (0, *mids, n)
                weights = [weight(s[left:right]) for left, right in zip(ends, ends[1:])]
                if all(value is not None for value in weights):
                    costs.append(sum(weights))
        best = min(costs, default=INF)
        count = len(costs)
        optimal = costs.count(best)
    else:
        @lru_cache(None)
        def suffix(start, remaining):
            if start == n:
                return (0, 1, 1) if remaining in (None, 0) else (INF, 0, 0)
            if remaining == 0:
                return INF, 0, 0
            best, count, optimal = INF, 0, 0
            for end in range(start + 1, n + 1):
                value = weight(s[start:end])
                if value is None:
                    continue
                rest, ways, tied = suffix(end, None if remaining is None else remaining - 1)
                count = (count + ways) % MOD
                if rest == INF:
                    continue
                candidate = value + rest
                if candidate < best:
                    best, optimal = candidate, tied
                elif candidate == best:
                    optimal = (optimal + tied) % MOD
            return best, count, optimal

        best, count, optimal = suffix(0, exact)
    if code == 400:
        return str(int(best != INF))
    if code in (401, 403, 431):
        return str(count % MOD)
    if code == 452:
        return "-1 0" if best == INF else f"{best} {optimal % MOD}"
    return str(-1 if best == INF else best)


def align(a, b, insertion, deletion, pairing, opening=0):
    """Propagate paths forward, with a new cost only when a gap opens."""
    n, m = len(a), len(b)
    table = [[[(INF, 0) for _ in range(3)] for _ in range(m + 1)] for _ in range(n + 1)]
    table[0][0][0] = (0, 1)

    def send(i, j, kind, cost, ways):
        old_cost, old_ways = table[i][j][kind]
        if cost < old_cost:
            table[i][j][kind] = cost, ways
        elif cost == old_cost:
            table[i][j][kind] = cost, (old_ways + ways) % MOD

    for i in range(n + 1):
        for j in range(m + 1):
            for kind, (cost, ways) in enumerate(table[i][j]):
                if cost == INF:
                    continue
                if i < n and j < m:
                    send(i + 1, j + 1, 0, cost + pairing(a[i], b[j]), ways)
                if j < m:
                    send(i, j + 1, 1, cost + insertion[j] + (opening if kind != 1 else 0), ways)
                if i < n:
                    send(i + 1, j, 2, cost + deletion[i] + (opening if kind != 2 else 0), ways)
    best = min(cost for cost, _ in table[n][m])
    return best, sum(ways for cost, ways in table[n][m] if cost == best) % MOD


def distance(a, b):
    """Ordinary edit distance by a suffix table."""
    n, m = len(a), len(b)
    nxt = list(range(m, -1, -1))
    for i in range(n - 1, -1, -1):
        row = [0] * (m + 1)
        row[m] = n - i
        for j in range(m - 1, -1, -1):
            row[j] = min(1 + nxt[j], 1 + row[j + 1], nxt[j + 1] + (a[i] != b[j]))
        nxt = row
    return nxt[0]


def edit_answer(code, data):
    lines = data.splitlines()
    a, b = lines[1:3]
    n, m = len(a), len(b)
    if code == 501:
        if m > n:
            return "-1"
        if n <= 12:
            return str(min(n - m + sum(a[i] != y for i, y in zip(indices, b))
                           for indices in combinations(range(n), m)))
        return str(align(a, b, [10**12] * m, [1] * n, lambda x, y: int(x != y))[0])
    if code == 502:
        @lru_cache(None)
        def cost(i):
            if i == n:
                return 0
            best = int(a[i] != b[i]) + cost(i + 1)
            if a[i:i+2][::-1] == b[i:i+2] and i + 1 < n:
                best = min(best, 1 + cost(i + 2))
            return best
        return str(cost(0))
    if code == 552:
        answer = min((distance(a, b[left:right]), left + 1, right)
                     for left in range(m) for right in range(left + 1, m + 1))
        return " ".join(map(str, answer))
    if code in (500, 551):
        cost = distance(a, b)
        if code == 551 and cost > int(lines[0].split()[2]):
            return "-1"
        return str(cost)
    ins, delete, rep, opening = [1] * m, [1] * n, 1, 0
    if code == 503:
        i, d, rep = map(int, lines[3].split())
        ins, delete = [i] * m, [d] * n
    if code == 531:
        rep = int(lines[3])
        delete, ins = [list(map(int, row.split())) for row in lines[4:6]]
    if code == 550:
        opening, extension, rep = map(int, lines[3].split())
        ins, delete = [extension] * m, [extension] * n
    cost, ways = align(a, b, ins, delete, lambda x, y: rep * (x != y and y != "?"), opening)
    return f"{cost} {ways}" if code == 532 else str(cost)


@lru_cache(None)
def compositions(n, limit):
    counts = [1]
    total = 1
    for i in range(1, n + 1):
        counts.append(total)
        total += counts[i]
        if i >= limit:
            total -= counts[i - limit]
        total %= MOD
    return counts[n]


@lru_cache(None)
def distinct_parts(n):
    counts = [1] + [0] * n
    for part in range(1, n + 1):
        for total in range(n, part - 1, -1):
            counts[total] = (counts[total] + counts[total - part]) % MOD
    return counts[n]


def maximum_answer(code, data, seed):
    """Cases use fixed patterns with combinatorial or length lower bounds."""
    n = int(data.split(maxsplit=1)[0])
    if code == 451:
        return str(distinct_parts(n) if seed in (0, 3) else int(seed == 2))
    if code == 401 and seed == 0:
        return str(compositions(n, 2))
    if code == 403 and seed in (0, 3):
        return str(compositions(n, 50 if seed == 0 else 2))
    if code == 431 and seed in (0, 3):
        return str(comb(n - 1, 99) % MOD)
    if code == 532 and seed == 3:
        return f"1000 {comb(n, 1000) % MOD}"
    table = {
        400: [1, 1, 0, 1],
        401: [None, 1, 0, 1],
        402: [n // 4, -1, n // 2, n // 10],
        403: [None, 1, 1, None],
        430: [7 * n // 5, 10**9 * (n // 100), -1, 0],
        431: [None, 0, 1, None],
        432: [(n + 25) // 26, -1, n // 2, n],
        450: [0, 1, n // 2, 0],
        452: [f"{(n+2)//3} {(n+2)//3}", f"{n//2} 1", "-1 0", f"{n//2} 1"],
        500: [n, 0, 1, 1],
        501: [n, 0, 1, -1],
        502: [n // 2, 0, n, n],
        503: [n * 10**9, 0, 5, 9],
        530: [n, 0, 0, 1],
        531: [n * 10**9, 0, 5, 0],
        532: [f"{n} 1", "0 1", "1 1", None],
        550: [n * 10**9, 0, 4, 8],
        551: [-1, 0, 1, 50],
        552: [f"{n} 1 1", f"0 1 {n}", f"1 1 {n-1}", f"1 1 {n-1}"],
    }
    return str(table[code][seed])


def answer(code, data, maximum_seed=None):
    if maximum_seed is not None:
        return maximum_answer(code, data, maximum_seed)
    if code < 500:
        return partition_answer(code, data)
    return edit_answer(code, data)
