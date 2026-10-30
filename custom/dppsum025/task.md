# PREFIX025 — So sánh với một số cố định

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, số nguyên $K$ và $Q$ truy vấn. $K$ dùng chung cho mọi truy vấn. Với mỗi truy vấn $L,R$, hãy đếm riêng số phần tử nhỏ hơn $K$, bằng $K$ và lớn hơn $K$ trong đoạn $[L,R]$. Mỗi phần tử thuộc đúng một trong ba nhóm.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in ba số nguyên trên một dòng, lần lượt là số phần tử nhỏ hơn $K$, bằng $K$, lớn hơn $K$ trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.
- $-10^9\le K\le10^9$.

### Sample Input 1

```text
6 3 3
1 3 5 3 -2 7
1 6
2 4
5 5
```

### Sample Output 1

```text
2 2 2
0 2 1
1 0 0
```

### Sample Input 2

```text
3 2 0
0 0 0
1 3
2 2
```

### Sample Output 2

```text
0 3 0
0 1 0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, số phần tử nhỏ hơn, bằng và lớn hơn $3$ lần lượt là $2,2,2$. Với đoạn $[2,4]$, số phần tử nhỏ hơn, bằng và lớn hơn $3$ lần lượt là $0,2,1$. Với đoạn $[5,5]$, số phần tử nhỏ hơn, bằng và lớn hơn $3$ lần lượt là $1,0,0$.

Ở ví dụ 2: Với đoạn $[1,3]$, số phần tử nhỏ hơn, bằng và lớn hơn $0$ lần lượt là $0,3,0$. Với đoạn $[2,2]$, số phần tử nhỏ hơn, bằng và lớn hơn $0$ lần lượt là $0,1,0$.
