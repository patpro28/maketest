# ICPC0711E — Thành phần liên thông

### Đề bài

Cho đồ thị vô hướng $G$ gồm $N$ đỉnh và $M$ cạnh. Xây dựng đồ thị $GG$ gồm $N^2$ đỉnh mang nhãn $(a,b)$, với $1\le a,b\le N$. Hai đỉnh $(a,b)$ và $(c,d)$ được nối nếu $G$ có cả cạnh $(a,c)$ và cạnh $(b,d)$.

Hãy đếm số thành phần liên thông của $GG$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Mỗi dòng trong $M$ dòng tiếp theo chứa hai số nguyên $u,v$ mô tả một cạnh vô hướng của $G$.

### Dữ liệu ra

In số thành phần liên thông của $GG$.

### Ràng buộc

- $2\le N\le10^5$.
- $0\le M\le2\cdot10^5$.
- $1\le u,v\le N$.

### Sample Input 1

```text
3 1
1 2
```

### Sample Output 1

```text
7
```

### Sample Input 2

```text
10 0
```

### Sample Output 2

```text
100
```

### Sample Input 3

```text
6 4
1 2
3 4
4 5
2 6
```

### Sample Output 3

```text
8
```

### Giải thích

Ở ví dụ 1, hai thành phần có nhiều hơn một đỉnh là $\{(1,1),(2,2)\}$ và $\{(1,2),(2,1)\}$. Năm đỉnh có ít nhất một tọa độ bằng $3$ đều cô lập, nên có $7$ thành phần.

Ở ví dụ 2, cả $100$ đỉnh đều cô lập. Ở ví dụ 3, $G$ có hai thành phần liên thông hai phía, mỗi cặp có thứ tự của chúng tạo ra hai thành phần trong $GG$, tổng cộng $8$.
