# PREFIX13 — Tổng có trọng số

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Với mỗi truy vấn $L,R$, hãy tính tổng có trọng số $A_L+2A_{L+1}+\cdots+(R-L+1)A_R$. Trọng số bắt đầu lại từ $1$ ở đầu mỗi đoạn được hỏi.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng có trọng số được hỏi.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $-10^6\le A_i\le10^6$.
- $1\le L\le R\le N$.

### Sample Input 1

```text
4 3
2 -1 3 4
1 3
2 4
3 3
```

### Sample Output 1

```text
9
17
3
```

### Sample Input 2

```text
1 1
-5
1 1
```

### Sample Output 2

```text
-5
```

### Giải thích

Ở ví dụ 1, các tổng lần lượt là $2+2(-1)+3\cdot3=9$, $-1+2\cdot3+3\cdot4=17$ và $3$. Ở ví dụ 2, chỉ có một phần tử với trọng số $1$, nên kết quả là $-5$.
