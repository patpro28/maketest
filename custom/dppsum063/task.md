# PREFIX063 — Tổng lớn nhất với đủ số chia hết

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, đánh số từ $1$, và các số $K,T$.

Một đoạn được chấp nhận nếu gồm **đúng $K$ phần tử liên tiếp** và có **ít nhất $T$ phần tử** thỏa điều kiện: $A_i$ chia hết cho $M$.

Trong các đoạn được chấp nhận, hãy chọn đoạn có **tổng giá trị của tất cả $K$ phần tử lớn nhất**. Tổng này bao gồm cả phần tử không thỏa điều kiện. Nếu nhiều đoạn cùng đạt tổng lớn nhất, chọn đoạn có vị trí bắt đầu nhỏ nhất.

$M$ cố định cho cả dãy. Số $0$ chia hết cho mọi $M$ nguyên dương; số âm chia hết cho $M$ cũng được tính.

Nếu $T=0$, mọi đoạn dài đúng $K$ đều được chấp nhận. Nếu không có đoạn được chấp nhận, in `NONE`. Các đoạn phải nằm hoàn toàn trong dãy, không nối vòng. Các vị trí trùng giá trị được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa 4 số nguyên $N,K,T,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

Nếu tồn tại đoạn được chấp nhận, in hai số nguyên trên một dòng: tổng lớn nhất của đoạn được chọn và vị trí bắt đầu nhỏ nhất đạt tổng đó. Tổng có thể bằng $0$ hoặc âm.

Nếu không tồn tại đoạn được chấp nhận, in đúng chuỗi `NONE`.

### Ràng buộc

- $1\le K\le N\le200000$.
- $0\le T\le K$.
- $-10^9\le A_i\le10^9$.
- $1\le M\le10^9$.

### Sample Input 1

```text
6 2 1 3
1000000000 1000000000 -3 1 -3 1000000000
```

### Sample Output 1

```text
999999997 2
```

### Sample Input 2

```text
4 2 1 2
1 3 5 7
```

### Sample Output 2

```text
NONE
```

### Sample Input 3

```text
4 2 2 3
6 6 6 6
```

### Sample Output 3

```text
12 1
```

### Giải thích

Ở ví dụ 1, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(0,1,1,1,1)$, tổng toàn bộ từng đoạn là $(2000000000,999999997,-2,-2,999999997)$. Trong các đoạn có ít nhất $1$ phần tử phù hợp, tổng lớn nhất bằng $999999997$ và vị trí sớm nhất đạt tổng đó là $2$.

Ở ví dụ 2, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(0,0,0)$, tổng toàn bộ từng đoạn là $(4,8,12)$. Không đoạn nào có ít nhất $1$ phần tử phù hợp, nên in `NONE`.

Ở ví dụ 3, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(2,2,2)$, tổng toàn bộ từng đoạn là $(12,12,12)$. Trong các đoạn có ít nhất $2$ phần tử phù hợp, tổng lớn nhất bằng $12$ và vị trí sớm nhất đạt tổng đó là $1$.
