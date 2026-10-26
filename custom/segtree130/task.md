# SEGTREE130 — Mốc doanh thu

### Đề bài

Một công ty ghi nhận doanh thu trong $N$ ngày liên tiếp, ngày $i$ có doanh thu không âm $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: sửa doanh thu ngày $i$ thành $x$.
- `2 S`: tìm ngày sớm nhất $p$ sao cho tổng doanh thu từ ngày $1$ đến ngày $p$ đạt ít nhất $S$. Nếu tổng doanh thu cả dãy vẫn nhỏ hơn $S$, trả về $-1$.

Các ngày có doanh thu bằng $0$ vẫn nằm trong dãy và vẫn được đánh chỉ số như bình thường.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 S`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số ngày sớm nhất đạt mốc $S$ hoặc $-1$ nếu không thể đạt. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le S\le10^{18}$.

### Sample Input 1

```text
5 6
0 3 0 2 5
2 3
2 4
2 11
1 1 4
2 4
2 7
```

### Sample Output 1

```text
2
4
-1
1
2
```

### Sample Input 2

```text
3 4
1000000000 1000000000 1000000000
2 3000000000
2 3000000001
1 2 0
2 2000000000
```

### Sample Output 2

```text
3
-1
3
```

### Giải thích

Ở ví dụ 1, các tổng tiền tố ban đầu là $0,3,3,5,10$. Vì thế mốc $3$ được đạt đầu tiên ở ngày $2$, mốc $4$ ở ngày $4$, còn mốc $11$ không đạt được. Sửa ngày $1$ thành $4$ làm mốc $4$ đạt ngay ngày đầu và mốc $7$ đạt ở ngày $2$.

Ở ví dụ 2, tổng doanh thu ban đầu là $3\cdot10^9$. Sau khi sửa ngày $2$ về $0$, tổng $2\cdot10^9$ chỉ đạt tại ngày $3$.
