# PREFIX021 — Tổng số chẵn và số lẻ

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và $Q$ truy vấn. Mỗi truy vấn gồm hai chỉ số $L,R$. Hãy tính riêng tổng các phần tử chẵn và tổng các phần tử lẻ trong đoạn $[L,R]$, tính cả hai đầu mút. Số $0$ và các số âm chia hết cho $2$ cũng là số chẵn. Cộng đúng giá trị có dấu của từng phần tử.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in hai số nguyên trên một dòng: tổng các số chẵn, sau đó là tổng các số lẻ. Nhóm không có phần tử nào có tổng bằng $0$.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
6 3
-3 2 0 5 -4 7
1 6
2 5
1 1
```

### Sample Output 1

```text
-2 9
-2 5
0 -3
```

### Sample Input 2

```text
3 2
1000000000 1000000000 -1
1 3
3 3
```

### Sample Output 2

```text
2000000000 -1
0 -1
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, tổng các số chẵn bằng $-2$, tổng các số lẻ bằng $9$. Với đoạn $[2,5]$, tổng các số chẵn bằng $-2$, tổng các số lẻ bằng $5$. Với đoạn $[1,1]$, tổng các số chẵn bằng $0$, tổng các số lẻ bằng $-3$.

Ở ví dụ 2: Với đoạn $[1,3]$, tổng các số chẵn bằng $2000000000$, tổng các số lẻ bằng $-1$. Với đoạn $[3,3]$, tổng các số chẵn bằng $0$, tổng các số lẻ bằng $-1$.
