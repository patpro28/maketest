# PREFIX10 — Đếm số chẵn

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$. Hãy đếm số phần tử chẵn trong đoạn từ $L$ đến $R$, tính cả hai đầu mút. Số $0$ và các số nguyên âm chia hết cho $2$ cũng là số chẵn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số phần tử chẵn trong đoạn.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$.

### Sample Input 1

```text
5 3
2 -3 0 7 -4
1 5
2 4
4 4
```

### Sample Output 1

```text
3
1
0
```

### Sample Input 2

```text
1 1
-2
1 1
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, các số chẵn của cả dãy là $2,0,-4$; đoạn $[2,4]$ chỉ có số $0$; đoạn $[4,4]$ không có số chẵn. Ở ví dụ 2, số $-2$ là số chẵn.
