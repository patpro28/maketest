# PREFIX11 — Tổng xen kẽ

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Với mỗi truy vấn $L,R$, hãy tính tổng xen kẽ $A_L-A_{L+1}+A_{L+2}-\cdots+(-1)^{R-L}A_R$. Phần tử đầu tiên của đoạn luôn mang dấu cộng, không phụ thuộc vị trí của nó trong dãy ban đầu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng xen kẽ được hỏi.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$.

### Sample Input 1

```text
5 3
3 8 -2 5 1
1 3
2 5
3 3
```

### Sample Output 1

```text
-7
14
-2
```

### Sample Input 2

```text
2 2
-4 6
1 2
2 2
```

### Sample Output 2

```text
-10
6
```

### Giải thích

Ở ví dụ 1, các kết quả lần lượt là $3-8+(-2)=-7$, $8-(-2)+5-1=14$ và $-2$. Ở ví dụ 2, các tổng là $-4-6=-10$ và $6$.
