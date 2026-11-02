# PREFIX068 — Tổng lớn nhất với đủ số chứa chữ số 7

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, đánh số từ $1$, và các số $K,T$.

Một đoạn được chấp nhận nếu gồm **đúng $K$ phần tử liên tiếp** và có **ít nhất $T$ phần tử** thỏa điều kiện: biểu diễn thập phân của $A_i$ chứa chữ số `7`.

Trong các đoạn được chấp nhận, hãy chọn đoạn có **tổng giá trị của tất cả $K$ phần tử lớn nhất**. Tổng này bao gồm cả phần tử không thỏa điều kiện. Nếu nhiều đoạn cùng đạt tổng lớn nhất, chọn đoạn có vị trí bắt đầu nhỏ nhất.

Một phần tử chứa nhiều chữ số `7` vẫn chỉ được đếm một lần.

Nếu $T=0$, mọi đoạn dài đúng $K$ đều được chấp nhận. Nếu không có đoạn được chấp nhận, in `NONE`. Các đoạn phải nằm hoàn toàn trong dãy, không nối vòng. Các vị trí trùng giá trị được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa 3 số nguyên $N,K,T$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

Nếu tồn tại đoạn được chấp nhận, in hai số nguyên trên một dòng: tổng lớn nhất của đoạn được chọn và vị trí bắt đầu nhỏ nhất đạt tổng đó. Tổng có thể bằng $0$ hoặc âm.

Nếu không tồn tại đoạn được chấp nhận, in đúng chuỗi `NONE`.

### Ràng buộc

- $1\le K\le N\le200000$.
- $0\le T\le K$.
- $0\le A_i\le10^9$.

### Sample Input 1

```text
6 2 1
1000000000 1000000000 7 1 7 1000000000
```

### Sample Output 1

```text
1000000007 2
```

### Sample Input 2

```text
4 2 1
0 1 23 999999999
```

### Sample Output 2

```text
NONE
```

### Sample Input 3

```text
4 2 2
77 77 77 77
```

### Sample Output 3

```text
154 1
```

### Giải thích

Ở ví dụ 1, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(0,1,1,1,1)$, tổng toàn bộ từng đoạn là $(2000000000,1000000007,8,8,1000000007)$. Trong các đoạn có ít nhất $1$ phần tử phù hợp, tổng lớn nhất bằng $1000000007$ và vị trí sớm nhất đạt tổng đó là $2$.

Ở ví dụ 2, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(0,0,0)$, tổng toàn bộ từng đoạn là $(1,24,1000000022)$. Không đoạn nào có ít nhất $1$ phần tử phù hợp, nên in `NONE`.

Ở ví dụ 3, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(2,2,2)$, tổng toàn bộ từng đoạn là $(154,154,154)$. Trong các đoạn có ít nhất $2$ phần tử phù hợp, tổng lớn nhất bằng $154$ và vị trí sớm nhất đạt tổng đó là $1$.
