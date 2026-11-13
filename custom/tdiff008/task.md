# TDIFF008 — Hiệu tại vị trí được hỏi

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ và $Q$ câu hỏi. Mỗi câu hỏi cho bốn số $L,R,X,P$. Giả sử cộng $X$ vào mọi phần tử của đoạn $[L,R]$ trong dãy $A$ ban đầu, hãy tìm giá trị mảng hiệu tại vị trí $P$ sau phép cộng đó.

Mỗi câu hỏi bắt đầu từ cùng một dãy $A$ ban đầu.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa bốn số nguyên $L,R,X,P$ của một câu hỏi.

### Dữ liệu ra

Xử lý các bộ test theo thứ tự đầu vào. Trong mỗi bộ test, in một dòng cho mỗi câu hỏi theo thứ tự đã cho. Mỗi dòng chứa giá trị mảng hiệu tại vị trí $P$ sau phép cộng giả định.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|D_i|\le10^9$ với mọi $1\le i\le N$.
- $1\le Q\le 2\cdot 10^5$. Mỗi câu hỏi thỏa $1\le L\le R\le N$, $|X|\le10^9$ và $1\le P\le N$.
- Tổng số câu hỏi trên tất cả các bộ test thỏa $\sum_{i=1}^{T} Q_i \le 2\cdot 10^5$.

### Sample Input 1

```text
2
5 5
3 -1 2 0 -4
2 4 5 2
2 4 5 5
2 4 5 3
1 5 -3 1
2 4 5 2
1 1
8
1 1 -3 1
```

### Sample Output 1

```text
4
-9
2
0
4
5
```

### Sample Input 2

```text
1
3 3
7 -2 4
3 3 6 3
1 1 -5 2
2 3 0 2
```

### Sample Output 2

```text
10
3
-2
```

### Giải thích

**Ví dụ 1, bộ test thứ nhất**

Cộng dồn $D=(3,-1,2,0,-4)$ được dãy ban đầu $A=(3,2,4,4,0)$. Với từng câu hỏi, áp dụng phép cộng lên dãy ban đầu rồi tính lại phần tử $D_P$ được hỏi.

| Câu hỏi | Phép cộng | Dãy $A$ sau phép cộng | Giá trị được hỏi |
| --- | --- | --- | --- |
| 1 | Cộng $5$ vào $[2,4]$ | $(3,7,9,9,0)$ | $D_2=7-3=4$ |
| 2 | Cộng $5$ vào $[2,4]$ | $(3,7,9,9,0)$ | $D_5=0-9=-9$ |
| 3 | Cộng $5$ vào $[2,4]$ | $(3,7,9,9,0)$ | $D_3=9-7=2$ |
| 4 | Cộng $-3$ vào $[1,5]$ | $(0,-1,1,1,-3)$ | $D_1=A_1=0$ |
| 5 | Cộng $5$ vào $[2,4]$ | $(3,7,9,9,0)$ | $D_2=7-3=4$ |

**Ví dụ 1, bộ test thứ hai**

1. Từ $D=(8)$, khôi phục được $A=(8)$.
2. Cộng $-3$ vào vị trí $1$, được $A=(5)$.
3. Giá trị được hỏi là $D_1=A_1=5$.

**Ví dụ 2**

Cộng dồn $D=(7,-2,4)$ được dãy ban đầu $A=(7,5,9)$. Mỗi câu hỏi lại bắt đầu từ dãy này.

| Câu hỏi | Phép cộng | Dãy $A$ sau phép cộng | Giá trị được hỏi |
| --- | --- | --- | --- |
| 1 | Cộng $6$ vào $[3,3]$ | $(7,5,15)$ | $D_3=15-5=10$ |
| 2 | Cộng $-5$ vào $[1,1]$ | $(2,5,9)$ | $D_2=5-2=3$ |
| 3 | Cộng $0$ vào $[2,3]$ | $(7,5,9)$ | $D_2=5-7=-2$ |
