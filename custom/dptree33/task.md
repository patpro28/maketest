# DPTREE33 — Nhánh cây dài nhất

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$, có gốc là đỉnh $1$.

Một người con của đỉnh $u$ là đỉnh kề với $u$ và ở xa gốc hơn $u$. Lá là đỉnh không có người con nào.

Với mỗi đỉnh $u$, hãy tìm số cạnh lớn nhất của một đường đi bắt đầu tại $u$, chỉ đi xuống các người con và kết thúc tại một lá trong cây con của $u$.

Nếu $u$ là lá, đường đi chỉ gồm chính $u$ có độ dài bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây.

### Dữ liệu ra

In $N$ số nguyên trên một dòng. Số thứ $u$ là độ dài đường đi xuống dài nhất từ $u$ đến một lá trong cây con của nó, tính theo số cạnh.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây có gốc $1$.

### Sample Input 1

```text
5
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
2 0 1 0 0
```

### Sample Input 2

```text
3
1 2
2 3
```

### Sample Output 2

```text
2 1 0
```

### Giải thích

Ở ví dụ 1, từ đỉnh $1$ có thể đi xuống theo đường $1\to3\to4$ hoặc $1\to3\to5$, mỗi đường dài $2$ cạnh. Từ đỉnh $3$ đi xuống một lá xa nhất cần $1$ cạnh. Các đỉnh $2,4,5$ là lá nên có kết quả $0$.

Ở ví dụ 2, từ đỉnh $1$ đến lá $3$ có $2$ cạnh, từ đỉnh $2$ đến lá $3$ có $1$ cạnh và đỉnh $3$ là lá.
