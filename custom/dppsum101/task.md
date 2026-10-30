# PREFIX01 — Ngày lập kỷ lục

### Đề bài

Cho nhiệt độ $A_i$ của $N$ ngày liên tiếp. Ngày $i$ với $i\ge2$ lập kỷ lục nếu $A_i$ lớn hơn nhiệt độ của **mọi** ngày trước đó hoặc nhỏ hơn nhiệt độ của **mọi** ngày trước đó. Nhiệt độ bằng một kỷ lục cũ không tạo kỷ lục mới.

Hãy đếm số ngày lập kỷ lục. Không tính ngày đầu tiên.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số ngày lập kỷ lục.

### Ràng buộc

- $1\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
6
20 20 18 25 19 17
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4
5 5 5 5
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, ngày $3$ lập kỷ lục thấp mới, ngày $4$ lập kỷ lục cao mới và ngày $6$ lập kỷ lục thấp mới. Ở ví dụ 2, nhiệt độ không đổi nên không có ngày lập kỷ lục.
