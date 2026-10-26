# SEGTREE014 — Ghi nhận doanh số

### Đề bài

Có $N$ cửa hàng được đánh số từ $1$ đến $N$. Ban đầu, cửa hàng $i$ đã ghi nhận doanh số $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: cộng thêm $x$ vào doanh số của cửa hàng $i$, tức là thay $A_i$ bằng $A_i+x$.
- `2 l r`: tính tổng doanh số của các cửa hàng từ $l$ đến $r$.

Doanh số ban đầu và mỗi khoản cộng thêm đều không âm. Đây là phép cộng thêm, không phải phép gán. Mỗi truy vấn sử dụng doanh số sau tất cả thao tác ghi nhận trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả doanh số ban đầu của các cửa hàng.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa tổng doanh số trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$ với các giá trị ban đầu; $0\le x\le10^9$ với mỗi khoản cộng thêm. Doanh số hiện tại có thể lớn hơn $10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
4 6
2 0 5 3
2 1 4
1 2 4
2 2 3
1 3 2
1 3 2
2 1 3
```

### Sample Output 1

```text
10
9
15
```

### Sample Input 2

```text
1 5
1000000000
1 1 1000000000
1 1 1000000000
2 1 1
1 1 0
2 1 1
```

### Sample Output 2

```text
3000000000
3000000000
```

### Giải thích

Ở ví dụ 1, tổng doanh số ban đầu là $10$. Sau khi cộng $4$ vào cửa hàng $2$, đoạn $[2,3]$ có tổng $4+5=9$. Hai lần cộng $2$ vào cửa hàng $3$ làm doanh số cửa hàng này từ $5$ thành $9$; tổng trên đoạn $[1,3]$ là $2+4+9=15$.

Ở ví dụ 2, hai khoản cộng thêm làm doanh số tăng từ $10^9$ lên $3\cdot10^9$. Cộng thêm $0$ không làm doanh số thay đổi.
