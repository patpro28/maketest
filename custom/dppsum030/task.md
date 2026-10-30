# PREFIX030 — Tổng mức tăng liên tiếp

### Đề bài

Cho mức nước $A_i$ ghi nhận tại $N$ thời điểm và $Q$ truy vấn. Từ thời điểm $i$ đến $i+1$, nếu mức nước tăng thì độ tăng là $A_{i+1}-A_i$; nếu mức nước giảm hoặc giữ nguyên thì độ tăng được tính bằng $0$. Với mỗi truy vấn $L,R$, hãy tính tổng các độ tăng từ thời điểm $L$ đến thời điểm $R$. Không trừ các lần giảm khỏi tổng và không tính thay đổi từ thời điểm $L-1$ đến $L$. Nếu $L=R$, tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng các độ tăng trong đoạn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
6 3
2 7 4 4 9 3
1 6
2 5
4 4
```

### Sample Output 1

```text
10
5
0
```

### Sample Input 2

```text
3 2
9 5 1
1 3
2 3
```

### Sample Output 2

```text
0
0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, tổng các độ tăng bằng $10$. Với đoạn $[2,5]$, tổng các độ tăng bằng $5$. Với đoạn $[4,4]$, tổng các độ tăng bằng $0$.

Ở ví dụ 2: Với đoạn $[1,3]$, tổng các độ tăng bằng $0$. Với đoạn $[2,3]$, tổng các độ tăng bằng $0$.
