# PREFIX029 — Số lần đổi tính chẵn lẻ

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và $Q$ truy vấn. Một lần đổi tính chẵn lẻ xảy ra khi hai phần tử liên tiếp gồm một số chẵn và một số lẻ. Với mỗi truy vấn $L,R$, hãy đếm số cặp vị trí $(i,i+1)$ như vậy với $L\le i<R$. Số $0$ là số chẵn; số âm cũng được phân loại chẵn lẻ như bình thường. Không xét phần tử trước $L$. Nếu $L=R$, kết quả bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số lần đổi tính chẵn lẻ trong đoạn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
6 3
-3 2 4 5 0 -1
1 6
2 5
3 3
```

### Sample Output 1

```text
4
2
0
```

### Sample Input 2

```text
3 2
-3 -1 1
1 3
1 2
```

### Sample Output 2

```text
0
0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, có $4$ lần đổi tính chẵn lẻ. Với đoạn $[2,5]$, có $2$ lần đổi tính chẵn lẻ. Với đoạn $[3,3]$, có $0$ lần đổi tính chẵn lẻ.

Ở ví dụ 2: Với đoạn $[1,3]$, có $0$ lần đổi tính chẵn lẻ. Với đoạn $[1,2]$, có $0$ lần đổi tính chẵn lẻ.
