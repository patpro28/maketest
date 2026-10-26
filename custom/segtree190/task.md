# SEGTREE190 — Bảng điều phối

### Đề bài

Có $N$ kho được đánh số từ $1$ đến $N$. Kho $i$ có lượng hàng không âm $A_i$. Một kho được gọi là **có hàng** nếu $A_i>0$.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: đặt lượng hàng tại kho $i$ thành $x$.
- `2 x`: tìm kho có chỉ số nhỏ nhất có ít nhất $x$ đơn vị hàng.
- `3 S`: tìm chỉ số nhỏ nhất $p$ sao cho tổng lượng hàng từ kho $1$ đến kho $p$ đạt ít nhất $S$.
- `4 k`: liệt kê các kho có hàng theo chỉ số tăng dần và tìm chỉ số kho thứ $k$ trong danh sách đó.

Nếu một trong các thao tác tìm kiếm không có kết quả, trả về $-1$. Tất cả thao tác tìm kiếm chỉ tra cứu, không lấy hàng hay thay đổi lượng hàng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x`, `2 x`, `3 S` hoặc `4 k`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, $3$ hoặc $4$, in một dòng chứa chỉ số tìm được hoặc $-1$ nếu không tồn tại. Nếu chỉ có thao tác loại $1$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$, $0\le x\le10^9$.
- Với thao tác loại $2$: $1\le x\le10^9$.
- Với thao tác loại $3$: $1\le S\le10^{18}$.
- Với thao tác loại $4$: $1\le k\le N$.

### Sample Input 1

```text
5 8
0 4 0 2 7
2 3
3 6
4 2
1 2 0
2 3
3 10
4 2
4 3
```

### Sample Output 1

```text
2
4
4
5
-1
5
-1
```

### Sample Input 2

```text
1 7
0
2 1
3 1
4 1
1 1 5
2 5
3 5
4 1
```

### Sample Output 2

```text
-1
-1
-1
1
1
1
```

### Giải thích

Ở ví dụ 1, kho đầu tiên có ít nhất $3$ đơn vị là kho $2$. Tổng tiền tố đạt $6$ tại kho $4$, cũng là kho có hàng thứ $2$ trong danh sách $2,4,5$. Sau khi đặt kho $2$ về $0$, kho $5$ là nơi đầu tiên có ít nhất $3$ đơn vị; tổng cả dãy chỉ bằng $9$ nên không đạt mốc $10$. Danh sách kho có hàng lúc này là $4,5$.

Ở ví dụ 2, cả ba kiểu tìm kiếm đều thất bại khi kho duy nhất rỗng. Đặt kho này thành $5$ làm cả ba kiểu tìm kiếm tiếp theo cùng trả về chỉ số $1$.
