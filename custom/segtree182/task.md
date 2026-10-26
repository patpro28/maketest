# SEGTREE182 — Đủ tải và đạt độ phân giải

### Đề bài

Cho dãy số nguyên dương $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l S G`: tìm vị trí nhỏ nhất $r\in[l,N]$ sao cho đồng thời $\sum_{i=l}^{r}a_i\ge S$ và $\gcd(a_l,\ldots,a_r)\le G$. Nếu không có, in `-1`.

Cả hai điều kiện phải đúng trên cùng đoạn. Điều kiện GCD so sánh giá trị với $G$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le a_i,x,G\le10^9$; $1\le S\le10^{18}$; $1\le i,l\le N$.

### Sample Input 1

```text
5 6
6 10 15 5 1
2 1 10 2
2 2 10 1
2 4 7 5
1 5 2
2 4 7 1
2 3 1 4
```

### Sample Output 1

```text
2
5
-1
5
5
```

### Sample Input 2

```text
1 5
1000000000
2 1 1000000000 1000000000
2 1 1 999999999
1 1 1
2 1 1 1
2 1 1000000000000000000 1
```

### Sample Output 2

```text
1
-1
1
-1
```

### Giải thích

Ở ví dụ 1, đoạn $[1,2]$ có tổng $16$ và GCD bằng $2$, nên truy vấn đầu trả về $2$. Truy vấn thứ hai phải đến vị trí $5$ mới có GCD bằng $1$. Ban đầu đoạn $[4,5]$ có tổng $6$, không đủ $7$; sau cập nhật, tổng bằng $7$ và GCD bằng $1$. Truy vấn cuối cũng cần đến vị trí $5$. Ở ví dụ 2, các đáp án lần lượt là $1,-1,1,-1$.
