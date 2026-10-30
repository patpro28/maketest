# PREFIX18 — Tổng tích lũy nhiều ngày

### Đề bài

Một tài khoản ban đầu có số dư $0$. Vào ngày thứ $i$, tài khoản được cộng thêm $A_i$ đồng. Không có giao dịch rút tiền. Gọi $B_i$ là số dư cuối ngày $i$, sau khi đã nhận tiền của ngày đó. Với mỗi truy vấn $L,R$, hãy tính $B_L+B_{L+1}+\cdots+B_R$. Số dư mỗi ngày được tính từ ngày $1$, không bắt đầu lại tại ngày $L$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng các số dư cuối ngày được hỏi.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $0\le A_i\le10^6$.
- $1\le L\le R\le N$.

### Sample Input 1

```text
4 3
2 0 3 1
1 4
2 3
4 4
```

### Sample Output 1

```text
15
7
6
```

### Sample Input 2

```text
1 1
0
1 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, các số dư cuối ngày là $2,2,5,6$. Vì vậy ba kết quả là $15,7,6$. Ở ví dụ 2, số dư luôn bằng $0$.
