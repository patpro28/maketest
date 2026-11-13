# DPALL0001 — Đóng kiện đúng cân

### Đề bài

Có $N$ món đồ. Món thứ $i$ có khối lượng $W_i$ và giá trị $V_i$. Mỗi món được chọn tối đa một lần. Các món ở hai vị trí khác nhau là hai món riêng biệt, kể cả khi có cùng khối lượng và giá trị.

Hãy chọn các món có tổng khối lượng đúng bằng $W$ sao cho tổng giá trị lớn nhất. Có thể chọn tập rỗng, với khối lượng và giá trị đều bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,W$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $W_i,V_i$.

### Dữ liệu ra

In tổng giá trị lớn nhất nếu có thể đạt đúng khối lượng $W$. Nếu không thể, in $-1$.

### Ràng buộc

- $1\le N\le200$; $0\le W\le10000$.
- $1\le W_i\le10000$; $0\le V_i\le10^9$.

### Sample Input 1

```text
4 6
2 5
4 7
6 10
1 12
```

### Sample Output 1

```text
12
```

### Sample Input 2

```text
2 5
2 8
4 15
```

### Sample Output 2

```text
-1
```

### Giải thích

- Ví dụ 1. Hai món đầu có tổng khối lượng $6$ và tổng giá trị $12$, cao hơn giá trị $10$ khi lấy riêng món thứ ba.
- Ví dụ 2. Mọi khối lượng có thể đạt đều chẵn, nên không thể đạt đúng $5$.
