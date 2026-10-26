# SEGTREE173 — Chu kỳ còn trong giới hạn

### Đề bài

Cho dãy số nguyên dương $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l B`: tìm $r$ lớn nhất trong $[l,N]$ sao cho $\operatorname{lcm}(a_l,\ldots,a_r)\le B$.

LCM là bội chung nhỏ nhất. Nếu ngay $a_l>B$, in $l-1$, biểu thị đoạn rỗng. LCM của các phần tử có thể lớn hơn giới hạn số nguyên 64 bit.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le a_i,x\le10^9$; $1\le B\le10^{18}$; $1\le i,l\le N$.

### Sample Input 1

```text
5 5
2 3 4 5 6
2 1 12
2 2 3
2 4 4
1 4 1
2 2 12
```

### Sample Output 1

```text
3
2
3
5
```

### Sample Input 2

```text
3 4
999999937 999999929 999999893
2 1 1000000000000000000
1 2 1
2 1 1000000000000000000
2 3 1
```

### Sample Output 2

```text
2
3
2
```

### Giải thích

Ở ví dụ 1, LCM của đoạn $[1,3]$ là $12$ nhưng thêm $5$ làm LCM thành $60$. Truy vấn bắt đầu ở $4$ với giới hạn $4$ trả về $3$. Sau cập nhật, LCM của đoạn $[2,5]$ là $12$. Ở ví dụ 2, ban đầu chỉ ghép được hai phần tử đầu dưới ngưỡng; sau khi đổi phần tử giữa thành $1$, có thể ghép cả ba. Truy vấn cuối trả về $2$ vì phần tử ở vị trí $3$ lớn hơn $1$.
