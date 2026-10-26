# SEGTREE191 — Vòng tròn loại người

### Đề bài

Có $N$ người mang số từ $1$ đến $N$ ngồi thành vòng tròn theo thứ tự đó. Ban đầu bắt đầu đếm tại người số $1$.

Có $Q$ lượt. Ở lượt thứ $j$, nhận số nguyên dương $k_j$. Đi theo chiều số tăng và quay từ $N$ về $1$, chỉ đếm những người chưa bị loại; **người bắt đầu được tính là người thứ nhất**. Loại người thứ $k_j$ được đếm và in số của người đó. Nếu còn người, lượt tiếp theo bắt đầu tại người chưa bị loại kế tiếp theo chiều đếm.

Khi $k_j$ lớn hơn số người còn lại, tiếp tục đếm nhiều vòng nếu cần.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một số nguyên $k_j$.

### Dữ liệu ra

Sau mỗi lượt, in số của người bị loại trên một dòng.

### Ràng buộc

- $1\le Q\le N\le200000$.
- $1\le k_j\le10^{18}$.

### Sample Input 1

```text
5 5
2
2
2
2
2
```

### Sample Output 1

```text
2
4
1
5
3
```

### Sample Input 2

```text
4 4
1000000000000000000
1000000000000000000
2
2
```

### Sample Output 2

```text
4
1
3
2
```

### Giải thích

Ở ví dụ 1, thứ tự bị loại là $2,4,1,5,3$. Sau khi loại $4$, lượt tiếp theo bắt đầu tại $5$, nên người thứ hai được đếm là $1$. Ở ví dụ 2, hai bước đếm lớn loại lần lượt $4$ và $1$; sau đó loại $3$ rồi $2$.
