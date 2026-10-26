# SEGTREE160 — Sản phẩm lỗi trong lô

### Đề bài

Có $N$ sản phẩm được đánh số từ $1$ đến $N$. Số đo của sản phẩm $i$ là số nguyên $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: sửa số đo sản phẩm $i$ thành $x$.
- `2 l r u v`: chỉ xét các sản phẩm từ $l$ đến $r$, tìm chỉ số nhỏ nhất có số đo nằm ngoài đoạn cho phép $[u,v]$. Nếu mọi sản phẩm trong lô đều thuộc $[u,v]$, trả về $-1$.

Hai biên $u,v$ đều được chấp nhận. Chỉ số trả về là chỉ số trong cả dãy, không phải thứ tự tương đối trong lô. Mỗi truy vấn có thể dùng hai biên khác nhau.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r u v`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số sản phẩm lỗi đầu tiên trong đoạn được hỏi hoặc $-1$ nếu không tồn tại. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i,x,u,v\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$ và $u\le v$.

### Sample Input 1

```text
5 6
4 6 5 9 4
2 1 3 4 6
2 2 5 4 8
1 4 7
2 2 5 4 8
1 3 -1
2 2 4 0 10
```

### Sample Output 1

```text
-1
4
-1
3
```

### Sample Input 2

```text
1 4
-1000000000
2 1 1 -1000000000 -1000000000
2 1 1 0 1000000000
1 1 1000000000
2 1 1 0 1000000000
```

### Sample Output 2

```text
-1
1
-1
```

### Giải thích

Ở ví dụ 1, ba số đo đầu đều nằm trong $[4,6]$. Truy vấn tiếp theo tìm thấy sản phẩm $4$ có số đo $9>8$. Sau khi sửa số đo đó thành $7$, lô $[2,5]$ không còn sản phẩm lỗi theo hai biên này. Sửa sản phẩm $3$ thành $-1$ làm nó trở thành vị trí lỗi đầu tiên trong lô $[2,4]$ với khoảng cho phép $[0,10]$.

Ở ví dụ 2, giá trị bằng biên được chấp nhận; giá trị $-10^9$ nằm ngoài $[0,10^9]$.
