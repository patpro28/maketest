# SEGTREE140 — Phân phòng cho đoàn khách

### Đề bài

Có $N$ khách sạn được đánh số từ $1$ đến $N$. Ban đầu khách sạn $i$ còn $A_i$ phòng trống. Có $Q$ đoàn khách lần lượt đến đặt phòng; đoàn thứ $j$ cần $X_j$ phòng.

Với mỗi đoàn, hãy chọn khách sạn có chỉ số nhỏ nhất còn ít nhất $X_j$ phòng. Nếu tìm được khách sạn $p$, in $p$ và giảm số phòng trống của khách sạn đó đi $X_j$. Nếu không có khách sạn phù hợp, in $-1$ và giữ nguyên mọi số phòng.

Cả đoàn phải ở cùng một khách sạn. Các đoàn được xử lý theo đúng thứ tự đầu vào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa số nguyên $X_j$, là số phòng đoàn thứ $j$ cần.

### Dữ liệu ra

Với mỗi đoàn khách, in một dòng chứa chỉ số khách sạn được chọn hoặc $-1$ nếu không có khách sạn đủ phòng.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- $1\le X_j\le10^9$ với mọi đoàn khách.

### Sample Input 1

```text
4 6
3 1 5 2
2
3
2
2
1
2
```

### Sample Output 1

```text
1
3
3
4
1
-1
```

### Sample Input 2

```text
1 3
0
1
1000000000
1
```

### Sample Output 2

```text
-1
-1
-1
```

### Giải thích

Ở ví dụ 1, đoàn đầu nhận $2$ phòng ở khách sạn $1$, làm số phòng còn lại thành $1,1,5,2$. Hai đoàn tiếp theo lần lượt nhận $3$ rồi $2$ phòng ở khách sạn $3$. Đoàn thứ tư vào khách sạn $4$, đoàn thứ năm vào khách sạn $1$. Đoàn cuối không có khách sạn đủ $2$ phòng.

Ở ví dụ 2, khách sạn duy nhất không có phòng nên không nhận được đoàn nào.
