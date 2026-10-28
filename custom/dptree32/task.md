# DPTREE32 — Kho tài nguyên của một nhánh

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$, có gốc là đỉnh $1$. Đỉnh $i$ chứa $A_i$ đơn vị tài nguyên.

Với mỗi đỉnh $u$, cây con gốc $u$ gồm chính $u$ và tất cả các đỉnh mà đường đi từ gốc $1$ đến đỉnh đó đi qua $u$.

Hãy tính tổng tài nguyên trong cây con của từng đỉnh. Các kết quả được tính trên cây ban đầu; không có thao tác chuyển hoặc lấy tài nguyên.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây.

### Dữ liệu ra

In $N$ số nguyên trên một dòng. Số thứ $u$ là tổng tài nguyên trong cây con gốc $u$, kể cả tài nguyên tại chính $u$.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $0\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây có gốc $1$.

### Sample Input 1

```text
5
2 3 5 7 11
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
28 3 23 7 11
```

### Sample Input 2

```text
1
0
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, cây con gốc $3$ gồm các đỉnh $3,4,5$, có tổng tài nguyên $5+7+11=23$. Cây con gốc $1$ là toàn bộ cây, có tổng tài nguyên $28$. Các đỉnh $2,4,5$ là lá nên kết quả tại mỗi đỉnh bằng tài nguyên của chính đỉnh đó.

Ở ví dụ 2, cây chỉ có một đỉnh và tài nguyên của đỉnh đó bằng $0$.
