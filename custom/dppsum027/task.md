# PREFIX027 — Số lần tăng trong đoạn

### Đề bài

Cho nhiệt độ $A_i$ của $N$ ngày và $Q$ truy vấn. Với mỗi truy vấn $L,R$, hãy đếm số lần nhiệt độ tăng giữa hai ngày liên tiếp trong đoạn: đếm các chỉ số $i$ thỏa $L\le i<R$ và $A_{i+1}>A_i$. Nhiệt độ bằng nhau không được tính là tăng. Không so sánh ngày $L$ với ngày $L-1$. Nếu $L=R$, kết quả bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số lần nhiệt độ tăng trong đoạn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
6 3
2 5 5 1 4 3
1 6
2 5
3 3
```

### Sample Output 1

```text
2
1
0
```

### Sample Input 2

```text
2 2
8 3
1 2
2 2
```

### Sample Output 2

```text
0
0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, có $2$ lần tăng. Với đoạn $[2,5]$, có $1$ lần tăng. Với đoạn $[3,3]$, có $0$ lần tăng.

Ở ví dụ 2: Với đoạn $[1,2]$, có $0$ lần tăng. Với đoạn $[2,2]$, có $0$ lần tăng.
