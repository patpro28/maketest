# SEGTREE023 — Kiểm định chất lượng

### Đề bài

Có $N$ sản phẩm được đánh số từ $1$ đến $N$. Số đo của sản phẩm $i$ là số nguyên $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: sửa số đo của sản phẩm $i$ thành $x$.
- `2 l r u v`: kiểm tra xem mọi sản phẩm từ $l$ đến $r$ có số đo thuộc đoạn cho phép $[u,v]$ hay không.

Hai biên $u,v$ đều được tính: số đo bằng $u$ hoặc bằng $v$ vẫn đạt yêu cầu. Mỗi truy vấn có thể có một đoạn cho phép khác nhau và sử dụng các số đo sau tất cả thao tác sửa trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả số đo ban đầu của các sản phẩm.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r u v`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa `YES` nếu mọi số đo trong đoạn được hỏi đều thuộc $[u,v]$; ngược lại in `NO`. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x,u,v\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$, $u\le v$.

### Sample Input 1

```text
5 7
4 6 5 9 4
2 1 3 4 6
2 2 5 4 8
1 4 7
2 2 5 4 8
2 3 3 5 5
1 3 -1
2 1 3 0 10
```

### Sample Output 1

```text
YES
NO
YES
YES
NO
```

### Sample Input 2

```text
1 4
-1000000000
2 1 1 -1000000000 -1000000000
2 1 1 -999999999 1000000000
1 1 1000000000
2 1 1 -1000000000 1000000000
```

### Sample Output 2

```text
YES
NO
YES
```

### Giải thích

Ở ví dụ 1, ba số đo $4,6,5$ đều thuộc $[4,6]$. Truy vấn thứ hai không đạt vì sản phẩm $4$ có số đo $9>8$. Sau khi sửa số đo đó thành $7$, truy vấn cùng đoạn và cùng giới hạn cho kết quả `YES`. Số đo đúng bằng cả hai biên $5$ cũng đạt yêu cầu. Truy vấn cuối không đạt vì có số đo $-1<0$.

Ở ví dụ 2, số đo bằng biên cho phép vẫn được chấp nhận; số đo nhỏ hơn biên dưới thì không đạt.
