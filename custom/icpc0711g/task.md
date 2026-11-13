# ICPC0711G — Thứ tự xâu

### Đề bài

Cho $N$ xâu đôi một khác nhau, không xâu nào là tiền tố của xâu khác. Chọn $K$ xâu khác nhau rồi ghép theo một thứ tự. Có tất cả

$$T=\frac{N!}{(N-K)!}$$

xâu khác nhau được tạo thành theo cách này. Sắp xếp các xâu đó theo thứ tự từ điển, đánh số từ $1$.

Cho xâu $X$ được bảo đảm thuộc tập trên. Hãy tìm thứ tự của $X$, lấy phần dư khi chia cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Mỗi dòng trong $N$ dòng tiếp theo chứa một xâu $S_i$.
- Dòng cuối chứa xâu $X$.

### Dữ liệu ra

In thứ tự của $X$ trong danh sách đã sắp xếp, modulo $10^9+7$.

### Ràng buộc

- $1\le K\le N\le10^6$.
- Các xâu $S_i$ không rỗng; tổng độ dài của chúng không vượt quá $10^6$.
- Không xâu nào là tiền tố của một xâu khác.
- $X$ là phép ghép đúng $K$ xâu khác nhau trong các xâu đã cho.

### Sample Input 1

```text
4 3
a
b
c
d
acb
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
6 5
ab
bc
cd
ef
eh
f
abefcdbcf
```

### Sample Output 2

```text
56
```

### Giải thích

Ở ví dụ 1, các xâu đầu tiên là `abc`, `abd`, `acb`, `acd`, `adb`, `adc`, nên `acb` có thứ tự $3$. Ở ví dụ 2, $X$ được ghép từ `ab`, `ef`, `cd`, `bc`, `f` và có thứ tự $56$.
