# SEGTREE027 — Chênh lệch giữa hai khu vực

### Đề bài

Có $N$ vị trí được đánh số từ $1$ đến $N$. Tại vị trí $i$ có độ cao nguyên $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác.

- `1 i x` — gán độ cao tại vị trí $i$ bằng $x$.
- `2 l r u v` — chọn một vị trí $i$ trong khu vực $[l,r]$ và một vị trí $j$ trong khu vực $[u,v]$ sao cho chênh lệch độ cao $|A_i-A_j|$ lớn nhất. Hãy in chênh lệch lớn nhất đó.

Hai khu vực của mỗi truy vấn đều khác rỗng và khu vực thứ nhất nằm hoàn toàn trước khu vực thứ hai.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo dạng `1 i x` hoặc `2 l r u v`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chênh lệch lớn nhất có thể đạt được. In các kết quả theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le 200\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- Với thao tác loại $1$, $1\le i\le N$ và $|x|\le 10^9$.
- Với thao tác loại $2$, $1\le l\le r<u\le v\le N$.

### Sample Input 1

```text
6 6
-4 6 2 -7 1 6
2 1 2 3 5
2 3 3 5 6
1 4 8
2 1 2 4 6
1 1 6
2 1 2 6 6
```

### Sample Output 1

```text
13
4
12
0
```

### Sample Input 2

```text
2 3
-1000000000 1000000000
2 1 1 2 2
1 1 1000000000
2 1 1 2 2
```

### Sample Output 2

```text
2000000000
0
```

### Giải thích

Ở ví dụ 1, truy vấn đầu chọn hai vị trí có độ cao $6$ và $-7$. Truy vấn thứ hai chọn hai độ cao $2$ và $6$. Sau khi gán $A_4=8$, cặp $(-4,8)$ cho chênh lệch $12$. Trong truy vấn cuối, mọi vị trí được xét đều có độ cao $6$.

Ở ví dụ 2, mỗi khu vực gồm một vị trí. Sau lần gán, hai độ cao bằng nhau nên chênh lệch là $0$.
