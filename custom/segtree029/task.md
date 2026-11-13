# SEGTREE029 — Mức cao thứ hai

### Đề bài

Cho dãy số nguyên không âm $A_1,A_2,\ldots,A_N$. Bạn cần xử lý lần lượt $Q$ thao tác.

- `1 i x` — gán giá trị $A_i$ bằng $x$.
- `2 l r` — tìm giá trị lớn nhất trong đoạn $[l,r]$ mà nhỏ hơn giá trị lớn nhất của đoạn. Nếu mọi phần tử trong đoạn đều bằng nhau, kết quả là $-1$.

Chẳng hạn, đoạn gồm các giá trị $8,8,5,3$ có mức cao thứ hai bằng $5$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa mức cao thứ hai của đoạn, hoặc $-1$ nếu đoạn chỉ có một giá trị phân biệt. In các kết quả theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le 200\,000$.
- $0\le A_i\le 10^9$ với mọi giá trị ban đầu.
- Với thao tác loại $1$, $1\le i\le N$ và $0\le x\le 10^9$.
- Với thao tác loại $2$, $1\le l\le r\le N$.

### Sample Input 1

```text
6 7
8 8 3 5 5 0
2 1 6
2 1 2
1 2 4
2 1 3
1 1 3
2 1 3
2 4 6
```

### Sample Output 1

```text
5
-1
4
3
0
```

### Sample Input 2

```text
1 3
0
2 1 1
1 1 1000000000
2 1 1
```

### Sample Output 2

```text
-1
-1
```

### Giải thích

Ở ví dụ 1, đoạn đầu có các mức phân biệt $8,5,3,0$, nên mức cao thứ hai là $5$. Đoạn $[1,2]$ ban đầu chỉ có mức $8$. Sau từng lần gán, đoạn $[1,3]$ lần lượt có các mức phân biệt $\{8,4,3\}$ và $\{4,3\}$. Truy vấn cuối có hai mức $5$ và $0$.

Ở ví dụ 2, cả hai truy vấn đều chỉ xét một phần tử nên không có mức cao thứ hai.
