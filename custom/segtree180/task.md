# SEGTREE180 — Đoạn ổn định

### Đề bài

Cho dãy $N$ số nguyên không âm $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: gán $A_i=x$.
- `2 l B D`: tìm chỉ số $r$ lớn nhất, $l\le r\le N$, sao cho đoạn $[l,r]$ đồng thời có tổng không vượt $B$ và chênh lệch giữa giá trị lớn nhất với nhỏ nhất không vượt $D$.

Nếu không có đoạn không rỗng thỏa mãn, trả về $l-1$. Điểm bắt đầu $l$ luôn cố định trong truy vấn. Không được bỏ qua phần tử ở giữa. Đoạn một phần tử có chênh lệch max–min bằng $0$. Truy vấn không làm thay đổi dãy.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l B D`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số cuối xa nhất $r$ thỏa mãn cả hai điều kiện hoặc $l-1$ nếu đoạn phải rỗng. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le N$, $0\le B\le10^{18}$, $0\le D\le10^9$.

### Sample Input 1

```text
5 6
2 3 3 8 4
2 1 20 1
2 2 5 10
2 4 7 100
1 4 3
2 1 20 1
2 2 9 0
```

### Sample Output 1

```text
3
2
3
4
4
```

### Sample Input 2

```text
3 4
0 5 0
2 1 100 0
2 2 4 10
1 2 0
2 1 0 0
```

### Sample Output 2

```text
1
1
3
```

### Giải thích

Ở ví dụ 1, đoạn $[1,3]$ có tổng $8$ và chênh lệch $1$; thêm phần tử $8$ làm chênh lệch vượt $1$. Truy vấn thứ hai chỉ nhận được phần tử đầu vì hai phần tử $3,3$ đã có tổng $6>5$. Truy vấn bắt đầu ở vị trí $4$ với ngân sách $7$ phải rỗng nên trả về $3$. Sau khi gán $A_4=3$, đoạn $[1,4]$ đạt yêu cầu chênh lệch $1$, và ba phần tử $3$ trong đoạn $[2,4]$ đạt tổng $9$ với chênh lệch $0$.

Ở ví dụ 2, điều kiện chênh lệch $0$ ngăn nhận phần tử $5$ sau số $0$. Khi mọi phần tử được sửa về $0$, cả dãy thỏa mãn với ngân sách và chênh lệch đều bằng $0$.
