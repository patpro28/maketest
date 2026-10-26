# SEGTREE102 — Tín hiệu tương thích đầu tiên

### Đề bài

Cho $N$ mặt nạ bit $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 M`: tìm vị trí nhỏ nhất $i$ có $(a_i\mathbin{\mathrm{AND}}M)\ne0$. Nếu không có, in `-1`.

Hai mặt nạ tương thích khi có ít nhất một bit cùng bật. AND là phép toán AND trên bit.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le a_i,x<2^{20}$; $1\le M<2^{20}$; $1\le i\le N$.

### Sample Input 1

```text
5 6
0 2 4 3 8
2 1
2 6
2 16
1 1 5
2 4
2 8
```

### Sample Output 1

```text
4
2
-1
1
5
```

### Sample Input 2

```text
1 4
0
2 1048575
1 1 1048575
2 1
2 1048575
```

### Sample Output 2

```text
-1
1
1
```

### Giải thích

Ở ví dụ 1, mặt nạ $1$ tương thích đầu tiên với phần tử $3$ tại vị trí $4$; mặt nạ $6$ tương thích đầu tiên tại vị trí $2$. Ban đầu không có bit của $16$. Sau khi đổi phần tử đầu thành $5$, truy vấn mặt nạ $4$ trả về $1$. Ở ví dụ 2, các đáp án là $-1,1,1$.
