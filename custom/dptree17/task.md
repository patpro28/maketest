# DPTREE17 — Đếm tập độc lập

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$.

Một tập độc lập là một tập đỉnh sao cho không có hai đỉnh nào thuộc tập được nối trực tiếp bởi một cạnh. Hãy đếm số tập độc lập của cây, kể cả tập rỗng.

Hai tập được xem là khác nhau nếu tồn tại một đỉnh thuộc tập này nhưng không thuộc tập kia. Vì kết quả có thể rất lớn, hãy in số cách lấy dư cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh nối hai đỉnh $u$ và $v$.

### Dữ liệu ra

In một số nguyên là số tập độc lập của cây, lấy dư cho $10^9+7$.

### Ràng buộc

- $1\le N\le 2\cdot 10^5$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3
1 2
2 3
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
1
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, năm tập độc lập là $\varnothing$, $\{1\}$, $\{2\}$, $\{3\}$ và $\{1,3\}$.

Ở ví dụ 2, hai tập độc lập là tập rỗng và $\{1\}$.
