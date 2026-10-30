# PREFIX023 — Đếm và tính tổng số chia hết

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, số nguyên dương $K$ và $Q$ truy vấn. $K$ dùng chung cho mọi truy vấn. Với mỗi truy vấn $L,R$, hãy tìm số lượng phần tử chia hết cho $K$ và tổng giá trị của chính các phần tử đó trong đoạn $[L,R]$. Số $0$ chia hết cho mọi $K$ nguyên dương: số $0$ được tính vào số lượng nhưng chỉ đóng góp $0$ vào tổng. Các số âm chia hết cho $K$ cũng được chọn.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in hai số nguyên trên một dòng: số lượng phần tử chia hết cho $K$, sau đó là tổng giá trị của các phần tử đó. Nếu không có phần tử nào thỏa điều kiện, in `0 0`.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.
- $1\le K\le10^9$.

### Sample Input 1

```text
6 3 3
-6 0 5 9 -4 12
1 6
2 4
3 3
```

### Sample Output 1

```text
4 15
2 9
0 0
```

### Sample Input 2

```text
3 2 1
-1 0 2
1 3
2 2
```

### Sample Output 2

```text
3 1
1 0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, có $4$ phần tử chia hết cho $3$, tổng của chúng bằng $15$. Với đoạn $[2,4]$, có $2$ phần tử chia hết cho $3$, tổng của chúng bằng $9$. Với đoạn $[3,3]$, có $0$ phần tử chia hết cho $3$, tổng của chúng bằng $0$.

Ở ví dụ 2: Với đoạn $[1,3]$, có $3$ phần tử chia hết cho $1$, tổng của chúng bằng $1$. Với đoạn $[2,2]$, có $1$ phần tử chia hết cho $1$, tổng của chúng bằng $0$.
