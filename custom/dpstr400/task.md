# DPSTR400 — Lát xâu bằng mảnh cố định

### Đề bài

Cho xâu $S$ chỉ gồm `a` và `b`. Hãy xác định có thể chia toàn bộ xâu thành các đoạn liên tiếp, không rỗng, sao cho mỗi đoạn là một trong bốn mảnh `a`, `ab`, `ba`, `bb` hay không. Mỗi loại mảnh được dùng tùy ý nhiều lần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In `1` nếu chia được, ngược lại in `0`.

### Ràng buộc

- $1\le N\le 200000$.
- $S$ chỉ gồm `a` và `b`.

### Sample Input 1

```text
3
bba
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
1
b
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, có thể chia thành `bb | a`. Ở ví dụ 2, `b` không phải mảnh được phép.
