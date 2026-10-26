# PREFIX14 — Tổng hình chữ nhật

### Đề bài

Cho bảng số nguyên có $N$ hàng và $M$ cột, ô ở hàng $i$, cột $j$ có giá trị $A_{i,j}$. Các hàng và cột được đánh số từ $1$. Mỗi truy vấn gồm $X_1,Y_1,X_2,Y_2$, mô tả hình chữ nhật có góc trên trái $(X_1,Y_1)$ và góc dưới phải $(X_2,Y_2)$. Hãy tính tổng các ô trong hình chữ nhật, bao gồm các ô trên biên.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,Q$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa $M$ số nguyên $A_{i,1},\ldots,A_{i,M}$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên $X_1,Y_1,X_2,Y_2$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng các ô trong hình chữ nhật được hỏi.

### Ràng buộc

- $1\le N,M\le700$.
- $1\le Q\le200000$.
- $-10^9\le A_{i,j}\le10^9$.
- $1\le X_1\le X_2\le N$; $1\le Y_1\le Y_2\le M$.

### Sample Input 1

```text
2 3 3
1 2 3
-1 4 0
1 1 2 3
1 2 2 2
2 1 2 3
```

### Sample Output 1

```text
9
6
3
```

### Sample Input 2

```text
1 1 1
-7
1 1 1 1
```

### Sample Output 2

```text
-7
```

### Giải thích

Ở ví dụ 1, tổng toàn bảng là $9$; tổng cột thứ hai là $6$; tổng hàng thứ hai là $3$. Ở ví dụ 2, hình chữ nhật chỉ gồm ô có giá trị $-7$.
