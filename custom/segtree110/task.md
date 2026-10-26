# SEGTREE110 — Hai đầu khác màu

### Đề bài

Có $N$ ô xếp thành hàng, ô $i$ mang màu được biểu diễn bởi số nguyên $A_i$. Hai ô có cùng số biểu diễn thì có cùng màu.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: đổi màu ô $i$ thành $x$.
- `2 c`: tìm chỉ số nhỏ nhất và chỉ số lớn nhất của các ô có màu khác $c$ trong cả dãy. Nếu mọi ô đều có màu $c$, cả hai kết quả đều bằng $-1$.

Một truy vấn có thể trả về cùng một chỉ số ở cả hai kết quả nếu chỉ có một ô khác màu $c$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 c`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm hai số nguyên: chỉ số nhỏ nhất rồi đến chỉ số lớn nhất có màu khác $c$, cách nhau một dấu cách. Nếu không tồn tại, in `-1 -1`. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i,x,c\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.

### Sample Input 1

```text
5 6
2 2 3 2 4
2 2
2 3
1 3 2
2 2
1 5 2
2 2
```

### Sample Output 1

```text
3 5
1 5
5 5
-1 -1
```

### Sample Input 2

```text
1 4
7
2 7
2 8
1 1 8
2 8
```

### Sample Output 2

```text
-1 -1
1 1
-1 -1
```

### Giải thích

Ở ví dụ 1, ban đầu các ô khác màu $2$ là ô $3,5$. Khi hỏi màu $3$, ô $1$ và ô $5$ là hai vị trí ngoài cùng khác màu đó. Sau khi đổi ô $3$ về màu $2$, chỉ còn ô $5$ khác màu $2$. Đổi tiếp ô $5$ về màu $2$ làm cả hai kết quả bằng $-1$.

Ở ví dụ 2, khi màu được hỏi khác màu của ô duy nhất, cả hai chỉ số đều bằng $1$.
