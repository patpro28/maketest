"""Independent byte-level model, examples and oracle for introductory binary I/O."""
import struct

TITLES = [
    'Tổng giá trị trong tệp', 'Đếm học sinh đạt yêu cầu', 'Tổng tiền hàng',
    'Học sinh có tổng điểm cao nhất', 'Số dư cuối ngày', 'Thống kê ba loại sản phẩm',
    'Các điểm trên mặt phẳng', 'Tổng thời gian hoạt động', 'Sách còn trong kho',
    'Ngày có nhiệt độ cao nhất',
]
# Explicit padding matches the ordinary C++ struct layout on the judging machine.
FORMATS = ['<ii', '<ii', '<iiq', '<8s3i', '<B7xq', '<B3xi', '<ii', '<c3xi', '<12si', '<HBBi']
HEADERS = ['', '<ii', '<i', '<i', '<i4xq', '<i', '<i', '', '<i', '<4sI']
EXAMPLES = [
    [((), [(1, 7), (2, -3), (3, 5)]), ((), [(10, -4), (11, -6)])],
    [((4, 5), [(1, 8), (2, 4), (3, 5), (4, 0)]), ((2, 10), [(7, 3), (8, 9)])],
    [((2,), [(1, 3, 10000), (2, 2, 25000)]), ((2,), [(9, 0, 7000), (8, 4, 0)])],
    [((3,), [(b'AN', 8, 7, 9), (b'BINH', 9, 9, 9), (b'CHI', 10, 8, 9)]),
     ((1,), [(b'ABCDEFGH', 0, 0, 0)])],
    [((3, 100), [(1, 50), (2, 30), (2, 20)]), ((2, 0), [(2, 10), (1, 4)])],
    [((4,), [(1, 5), (3, 2), (1, 4), (2, 0)]), ((1,), [(2, 7)])],
    [((5,), [(1, 2), (-1, 3), (-2, -4), (5, -1), (0, 7)]),
     ((3,), [(0, 0), (2, 0), (0, -3)])],
    [((), [(b'R', 5), (b'S', 3), (b'R', 7)]), ((), [(b'S', 8), (b'S', 0)])],
    [((3,), [(b'TOAN', 4), (b'VAN', 0), (b'TIN', 2)]), ((1,), [(b'ABCDEFGHIJKL', 0)])],
    [((b'A109', 3), [(2026, 1, 2, 25), (2026, 1, 3, 28), (2026, 1, 4, 28)]),
     ((b'A109', 2), [(2025, 12, 1, -5), (2025, 12, 2, -8)])],
]


def encode(kind, header, rows):
    i = kind - 1
    return (struct.pack(HEADERS[i], *header) if HEADERS[i] else b'') + b''.join(
        struct.pack(FORMATS[i], *row) for row in rows)


def decode(kind, raw):
    i = kind - 1
    hs, rs = struct.calcsize(HEADERS[i]), struct.calcsize(FORMATS[i])
    assert len(raw) >= hs
    header = struct.unpack_from(HEADERS[i], raw) if hs else ()
    assert (len(raw) - hs) % rs == 0
    rows = list(struct.iter_unpack(FORMATS[i], raw[hs:]))
    if hs:
        assert len(rows) == (header[1] if kind == 10 else header[0])
    return header, rows


def oracle(kind, raw):
    h, a = decode(kind, raw)
    if kind == 1:
        return f'{sum(r[1] for r in a)}\n'
    if kind == 2:
        return f'{sum(r[1] >= h[1] for r in a)}\n'
    if kind == 3:
        return f'{sum(r[1] * r[2] for r in a)}\n'
    if kind == 4:
        # max keeps the first item in case of a tie.
        row = max(a, key=lambda r: sum(r[1:]))
        return f'{row[0].split(bytes([0]))[0].decode()} {sum(row[1:])}\n'
    if kind == 5:
        return f'{h[1] + sum(v if t == 1 else -v for t, v in a)}\n'
    if kind == 6:
        return ' '.join(str(sum(q for t, q in a if t == j)) for j in (1, 2, 3)) + '\n'
    if kind == 7:
        result = [0] * 5
        for x, y in a:
            j = 4 if x == 0 or y == 0 else (0 if x > 0 and y > 0 else
                1 if x < 0 and y > 0 else 2 if x < 0 and y < 0 else 3)
            result[j] += 1
        return ' '.join(map(str, result)) + '\n'
    if kind == 8:
        return f'{sum(t for s, t in a if s == b"R")}\n'
    if kind == 9:
        kept = [(s.split(bytes([0]))[0].decode(), q) for s, q in a if q > 0]
        return str(len(kept)) + '\n' + ''.join(f'{s} {q}\n' for s, q in kept)
    if kind == 10:
        y, m, d, t = max(a, key=lambda r: r[3])
        return f'{d} {m} {y} {t}\n'
    raise ValueError(kind)
