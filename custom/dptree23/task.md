# DPTREE23 — Bảo vệ các con đường

### Đề bài

Có $N$ ngôi làng, được đánh số từ $1$ đến $N$, và $N-1$ con đường hai chiều nối các làng tạo thành một cây.

Bạn có thể đặt tối đa một chốt bảo vệ tại mỗi làng. Chi phí đặt chốt tại làng $i$ là $C_i$. Một con đường được bảo vệ nếu **ít nhất một trong hai làng ở hai đầu con đường có chốt**.

Hãy chọn những làng đặt chốt sao cho tất cả các con đường đều được bảo vệ và tổng chi phí là nhỏ nhất. Nếu không có con đường nào, bạn được phép không đặt chốt.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $C_1,C_2,\ldots,C_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một con đường nối hai làng $u$ và $v$.

### Dữ liệu ra

In một số nguyên là tổng chi phí nhỏ nhất để bảo vệ tất cả các con đường.

### Ràng buộc

- $1\le N\le 2\cdot10^5$.
- $1\le C_i\le10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các con đường tạo thành một cây.

### Sample Input 1

```text
4
8 3 5 2
1 2
2 3
3 4
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
1
7
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, đặt chốt tại làng $2$ và làng $4$, tốn $3+2=5$. Cả ba con đường đều có ít nhất một đầu mút đặt chốt. Đây là chi phí nhỏ nhất.

Ở ví dụ 2, không có con đường nào nên không cần đặt chốt.
