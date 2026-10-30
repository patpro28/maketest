# PREFIX026 — Cặp số bằng nhau liên tiếp

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và $Q$ truy vấn. Với mỗi truy vấn $L,R$, hãy đếm số cặp vị trí liên tiếp $(i,i+1)$ thỏa $L\le i<R$ và $A_i=A_{i+1}$. Cả hai vị trí của một cặp đều phải nằm trong đoạn được hỏi. Các cặp được phép chung vị trí: ba phần tử bằng nhau liên tiếp tạo ra hai cặp. Nếu $L=R$, kết quả bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số cặp phần tử bằng nhau liên tiếp trong đoạn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
6 3
2 2 2 3 3 2
1 6
2 5
4 4
```

### Sample Output 1

```text
3
2
0
```

### Sample Input 2

```text
1 1
7
1 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, có $3$ cặp bằng nhau liên tiếp. Với đoạn $[2,5]$, có $2$ cặp bằng nhau liên tiếp. Với đoạn $[4,4]$, có $0$ cặp bằng nhau liên tiếp.

Ở ví dụ 2: Với đoạn $[1,1]$, có $0$ cặp bằng nhau liên tiếp.
