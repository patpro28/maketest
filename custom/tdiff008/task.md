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

Trong ví dụ 1, ở bộ thứ nhất, phép cộng $5$ vào $[2,4]$ làm $D_2=4$, $D_5=-9$ và giữ $D_3=2$. Câu hỏi thứ tư cho $D_1=3-3=0$. Câu hỏi thứ năm lặp lại câu hỏi đầu tiên nên đáp án vẫn là $4$. Bộ thứ hai cho $8-3=5$.

Trong ví dụ 2, câu hỏi thứ nhất làm $D_3$ tăng lên $10$. Câu hỏi thứ hai cộng $-5$ vào $[1,1]$, nên $D_2$ tăng lên $3$. Câu hỏi cuối cộng $0$ nên $D_2$ vẫn bằng $-2$.
