# DPTREE34 — Hành trình thu thập phần thưởng

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$, có gốc là đỉnh $1$. Mỗi đỉnh $i$ có phần thưởng $A_i$, có thể âm; phần thưởng âm làm giảm tổng nhận được.

Bạn xuất phát tại gốc $1$. Mỗi bước, bạn phải đi từ đỉnh hiện tại xuống một người con của nó. Hành trình **bắt buộc kết thúc tại một lá**, tức là một đỉnh không có con.

Tổng phần thưởng của hành trình là tổng giá trị tại tất cả các đỉnh được đi qua, kể cả gốc và lá cuối cùng. Bạn không được bỏ qua phần thưởng âm hay kết thúc sớm tại đỉnh có con.

Hãy tìm tổng phần thưởng lớn nhất có thể nhận được.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây.

### Dữ liệu ra

In một số nguyên là tổng phần thưởng lớn nhất trên một hành trình từ gốc đến một lá. Kết quả có thể âm.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $-10^9\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây có gốc $1$.

### Sample Input 1

```text
5
5 -2 4 -10 3
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
12
```

### Sample Input 2

```text
3
10 -20 -3
1 2
2 3
```

### Sample Output 2

```text
-13
```

### Giải thích

Ở ví dụ 1, chọn đường $1\to3\to5$, nhận tổng phần thưởng $5+4+3=12$. Hai hành trình còn lại kết thúc tại lá $2$ hoặc lá $4$ cho tổng lần lượt là $3$ và $-1$.

Ở ví dụ 2, chỉ có một hành trình hợp lệ là $1\to2\to3$, có tổng $10-20-3=-13$. Không được dừng tại đỉnh $1$ để nhận $10$.
