# DPTREE31 — Nhóm liên thông chia hết cho ba

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$.

Một tập đỉnh được gọi là liên thông nếu với hai đỉnh bất kỳ thuộc tập, mọi đỉnh trên đường đi duy nhất nối chúng cũng thuộc tập.

Hãy đếm số tập đỉnh **không rỗng, liên thông và có số phần tử chia hết cho $3$**. Hai tập khác nhau nếu tồn tại một đỉnh thuộc tập này nhưng không thuộc tập kia.

Vì kết quả có thể rất lớn, hãy in số tập lấy dư cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây.

### Dữ liệu ra

In một số nguyên là số tập đỉnh không rỗng, liên thông và có kích thước chia hết cho $3$, lấy dư cho $10^9+7$.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây.

### Sample Input 1

```text
4
1 2
1 3
1 4
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
6
1 2
2 3
3 4
4 5
5 6
```

### Sample Output 2

```text
5
```

### Giải thích

Ở ví dụ 1, ba tập hợp lệ là $\{1,2,3\}$, $\{1,2,4\}$ và $\{1,3,4\}$. Tập $\{2,3,4\}$ có ba đỉnh nhưng không liên thông.

Ở ví dụ 2, có bốn tập gồm ba đỉnh liên tiếp trên đường đi và một tập gồm cả sáu đỉnh, tổng cộng $5$ tập. Không tính tập rỗng dù kích thước $0$ chia hết cho $3$.
