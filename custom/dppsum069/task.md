# PREFIX069 — Tổng lớn nhất với đủ số có tổng chữ số H

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, đánh số từ $1$, và các số $K,T$.

Một đoạn được chấp nhận nếu gồm **đúng $K$ phần tử liên tiếp** và có **ít nhất $T$ phần tử** thỏa điều kiện: tổng các chữ số thập phân của $A_i$ bằng $H$.

Trong các đoạn được chấp nhận, hãy chọn đoạn có **tổng giá trị của tất cả $K$ phần tử lớn nhất**. Tổng này bao gồm cả phần tử không thỏa điều kiện. Nếu nhiều đoạn cùng đạt tổng lớn nhất, chọn đoạn có vị trí bắt đầu nhỏ nhất.

$H$ cố định cho cả dãy. Tổng chữ số của số $0$ bằng $0$. Điều kiện xét từng phần tử, không xét tổng chữ số của tổng đoạn.

Nếu $T=0$, mọi đoạn dài đúng $K$ đều được chấp nhận. Nếu không có đoạn được chấp nhận, in `NONE`. Các đoạn phải nằm hoàn toàn trong dãy, không nối vòng. Các vị trí trùng giá trị được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa 4 số nguyên $N,K,T,H$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

Nếu tồn tại đoạn được chấp nhận, in hai số nguyên trên một dòng: tổng lớn nhất của đoạn được chọn và vị trí bắt đầu nhỏ nhất đạt tổng đó. Tổng có thể bằng $0$ hoặc âm.

Nếu không tồn tại đoạn được chấp nhận, in đúng chuỗi `NONE`.

### Ràng buộc

- $1\le K\le N\le200000$.
- $0\le T\le K$.
- $0\le A_i\le10^9$.
- $0\le H\le81$.

### Sample Input 1

```text
6 2 1 1
999999999 999999999 1 2 1 999999999
```

### Sample Output 1

```text
1000000000 2
```

### Sample Input 2

```text
4 2 1 1
0 2 11 22
```

### Sample Output 2

```text
NONE
```

### Sample Input 3

```text
4 2 2 1
10 10 10 10
```

### Sample Output 3

```text
20 1
```

### Giải thích

Ở ví dụ 1, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(0,1,1,1,1)$, tổng toàn bộ từng đoạn là $(1999999998,1000000000,3,3,1000000000)$. Trong các đoạn có ít nhất $1$ phần tử phù hợp, tổng lớn nhất bằng $1000000000$ và vị trí sớm nhất đạt tổng đó là $2$.

Ở ví dụ 2, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(0,0,0)$, tổng toàn bộ từng đoạn là $(2,13,33)$. Không đoạn nào có ít nhất $1$ phần tử phù hợp, nên in `NONE`.

Ở ví dụ 3, theo thứ tự vị trí bắt đầu, số phần tử phù hợp của các đoạn là $(2,2,2)$, tổng toàn bộ từng đoạn là $(20,20,20)$. Trong các đoạn có ít nhất $2$ phần tử phù hợp, tổng lớn nhất bằng $20$ và vị trí sớm nhất đạt tổng đó là $1$.
