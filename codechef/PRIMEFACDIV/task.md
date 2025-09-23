### Đề bài

Một số nguyên dương $n > 1$ bất kỳ đều có thể phân tích dưới dạng thừa số nguyên tố như sau:

$$
n = p_1^{e_1} \cdot p_2^{e_2} \cdots p_k^{e_k}
$$

Trong đó:
- $p_1, p_2, \ldots, p_k$ là các số nguyên tố phân biệt.
- $e_1, e_2, \ldots, e_k$ là các số nguyên dương.

Ví dụ, số $60$ có thể được phân tích thành thừa số nguyên tố như sau:

$$
60 = 2^2 \cdot 3^1 \cdot 5^1
$$

Đặt $S(n)$ là tập các thừa số nguyên tố của $n$. Ví dụ, với $n = 60$, ta có: $S(60) = \{2, 3, 5\}$.

### Yêu cầu

Cho hai số nguyên dương $A$ và $B$, kiểm tra xem $A$ có chia hết cho mọi thừa số nguyên tố trong tập $S(B)$ hay không. Nếu có, in ra `YES`, ngược lại in ra `NO`.

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên $T$ ($1 \leq T \leq 10^5$) là số lượng bộ test.
- Mỗi bộ test gồm một dòng chứa hai số nguyên dương $A$ và $B$ ($1 \leq A, B \leq 10^{18}$).

### Dữ liệu ra

- Với mỗi bộ test, in ra `YES` nếu $A$ chia hết cho mọi thừa số nguyên tố của $B$, ngược lại in ra `NO`.

### Sample Input

```
3
21 63
72 72
25 20
```

### Sample Output

```
YES
YES
NO
```

### Giải thích

- Trong bộ test đầu tiên, $S(63) = \{3, 7\}$ và $21$ chia hết cho cả $3$ và $7$, nên in ra `YES`.
- Trong bộ test thứ hai, $S(72) = \{2, 3\}$ và $72$ chia hết cho cả $2$ và $3$, nên in ra `YES`.
- Trong bộ test thứ ba, $S(20) = \{2, 5\}$ và $25$ không chia hết cho $2$, nên in ra `NO`.