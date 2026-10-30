# PREFIX028 — Tổng độ lệch liên tiếp

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và $Q$ truy vấn. Với mỗi truy vấn $L,R$, hãy tính tổng độ lệch giữa các phần tử liên tiếp trong đoạn: $|A_{L+1}-A_L|+|A_{L+2}-A_{L+1}|+\cdots+|A_R-A_{R-1}|$. Chỉ xét các cặp có cả hai vị trí thuộc đoạn. Nếu $L=R$, tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng độ lệch giữa các phần tử liên tiếp trong đoạn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
5 3
2 7 4 4 -1
1 5
2 4
4 4
```

### Sample Output 1

```text
13
3
0
```

### Sample Input 2

```text
2 2
-1000000000 1000000000
1 2
2 2
```

### Sample Output 2

```text
2000000000
0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,5]$, tổng độ lệch giữa các phần tử liên tiếp bằng $13$. Với đoạn $[2,4]$, tổng độ lệch giữa các phần tử liên tiếp bằng $3$. Với đoạn $[4,4]$, tổng độ lệch giữa các phần tử liên tiếp bằng $0$.

Ở ví dụ 2: Với đoạn $[1,2]$, tổng độ lệch giữa các phần tử liên tiếp bằng $2000000000$. Với đoạn $[2,2]$, tổng độ lệch giữa các phần tử liên tiếp bằng $0$.
