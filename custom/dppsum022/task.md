# PREFIX022 — Tổng số dương và số âm

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và $Q$ truy vấn. Mỗi truy vấn gồm hai chỉ số $L,R$. Hãy tính riêng tổng các phần tử dương và tổng các phần tử âm trong đoạn $[L,R]$. Số $0$ không thuộc nhóm nào. Tổng các số âm được in đúng dấu âm, không lấy trị tuyệt đối.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in hai số nguyên trên một dòng: tổng các số dương, sau đó là tổng các số âm. Nhóm không có phần tử nào có tổng bằng $0$.

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
3 3
```

### Sample Output 1

```text
14 -7
7 -4
0 0
```

### Sample Input 2

```text
3 2
-1000000000 -1000000000 2
1 3
3 3
```

### Sample Output 2

```text
2 -2000000000
2 0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, tổng các số dương bằng $14$, tổng các số âm bằng $-7$. Với đoạn $[2,5]$, tổng các số dương bằng $7$, tổng các số âm bằng $-4$. Với đoạn $[3,3]$, tổng các số dương bằng $0$, tổng các số âm bằng $0$.

Ở ví dụ 2: Với đoạn $[1,3]$, tổng các số dương bằng $2$, tổng các số âm bằng $-2000000000$. Với đoạn $[3,3]$, tổng các số dương bằng $2$, tổng các số âm bằng $0$.
