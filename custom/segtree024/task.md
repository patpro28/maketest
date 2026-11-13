# SEGTREE024 — Độ lệch xa nhất

### Đề bài

Cho dãy số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần xử lý lần lượt $Q$ thao tác.

- `1 i x` — gán giá trị $A_i$ bằng $x$.
- `2 l r h` — tìm độ lệch lớn nhất so với mốc $h$ trong đoạn $[l,r]$. Độ lệch của phần tử $A_i$ là $|A_i-h|$.

Mỗi truy vấn dùng giá trị hiện tại của các phần tử và mốc $h$ được cho trong chính truy vấn đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo dạng `1 i x` hoặc `2 l r h`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa $\max_{l\le i\le r}|A_i-h|$. In các kết quả theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le 200\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- Với thao tác loại $1$, $1\le i\le N$ và $|x|\le 10^9$.
- Với thao tác loại $2$, $1\le l\le r\le N$ và $|h|\le 10^9$.

### Sample Input 1

```text
5 6
-4 7 2 -1 5
2 1 5 3
2 2 4 -2
1 2 -8
2 2 5 1
1 1 6
2 1 1 6
```

### Sample Output 1

```text
7
9
9
0
```

### Sample Input 2

```text
1 4
-1000000000
2 1 1 1000000000
1 1 1000000000
2 1 1 -1000000000
2 1 1 1000000000
```

### Sample Output 2

```text
2000000000
2000000000
0
```

### Giải thích

Ở ví dụ 1, giá trị $-4$ lệch $7$ so với mốc $3$. Truy vấn thứ hai dùng mốc $-2$ và giá trị xa nhất là $7$. Sau khi đổi $A_2$ thành $-8$, độ lệch của phần tử này so với mốc $1$ bằng $9$. Truy vấn cuối chỉ xét $A_1=6$, trùng với mốc.

Ở ví dụ 2, hai truy vấn đầu so sánh các giá trị ở hai đầu khoảng $[-10^9,10^9]$, nên độ lệch bằng $2\cdot 10^9$.
