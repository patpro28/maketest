# SEGTREE171 — Đoạn còn đủ ước chung

### Đề bài

Cho dãy số nguyên dương $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l G`: tìm chỉ số $r$ lớn nhất trong $[l,N]$ sao cho $\gcd(a_l,a_{l+1},\ldots,a_r)\ge G$.

Nếu ngay phần tử $a_l$ cũng không đạt điều kiện, in $l-1$, biểu thị đoạn rỗng. Điều kiện là **GCD không nhỏ hơn $G$**, không phải GCD chia hết cho $G$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le a_i,x,G\le10^9$; $1\le i,l\le N$.

### Sample Input 1

```text
5 5
12 18 6 10 15
2 1 6
2 2 7
2 4 11
1 4 30
2 1 6
```

### Sample Output 1

```text
3
2
3
4
```

### Sample Input 2

```text
3 5
7 7 7
2 2 1
2 2 7
2 2 8
1 2 1
2 1 7
```

### Sample Output 2

```text
3
3
1
1
```

### Giải thích

Ở ví dụ 1, GCD của đoạn $[1,3]$ là $6$, nhưng thêm phần tử $10$ làm GCD còn $2$. Từ vị trí $2$ với ngưỡng $7$, chỉ nhận được phần tử $18$. Từ vị trí $4$ với ngưỡng $11$, đáp án là $3$ vì $10<11$. Sau cập nhật, đoạn $[1,4]$ có GCD bằng $6$. Ở ví dụ 2, các đáp án lần lượt là $3,3,1,1$.
