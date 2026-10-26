# DPTREE29 — Tách hai nhóm đối địch

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$. Mỗi đỉnh có một trạng thái $T_i$:

- $T_i=0$: không được đánh dấu.
- $T_i=1$: được đánh dấu đỏ.
- $T_i=2$: được đánh dấu xanh.

Mỗi cạnh có một chi phí cắt. Bạn được phép cắt một số cạnh, làm cây tách thành các thành phần liên thông. Cần bảo đảm **không thành phần nào đồng thời chứa một đỉnh đỏ và một đỉnh xanh**.

Một thành phần có thể chứa nhiều đỉnh cùng màu hoặc không có đỉnh được đánh dấu. Bạn không được xóa đỉnh hay thay đổi màu của đỉnh.

Hãy tìm tổng chi phí cắt nhỏ nhất.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $T_1,T_2,\ldots,T_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa ba số nguyên $u,v,W$, mô tả một cạnh nối hai đỉnh $u,v$ có chi phí cắt là $W$.

### Dữ liệu ra

In một số nguyên là tổng chi phí cắt nhỏ nhất để mọi thành phần liên thông đều hợp lệ.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $T_i\in\{0,1,2\}$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- $0\le W\le10^9$.
- Các cạnh tạo thành một cây.

### Sample Input 1

```text
5
1 0 2 0 1
1 2 5
2 3 2
2 4 1
4 5 4
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3
1 0 1
1 2 7
2 3 9
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, cắt cạnh $(2,3)$ với chi phí $2$. Đỉnh xanh $3$ nằm riêng một thành phần, các đỉnh còn lại không chứa đỉnh xanh. Đây là chi phí nhỏ nhất.

Ở ví dụ 2, cây không có đỉnh xanh, nên toàn bộ cây đã hợp lệ và không cần cắt cạnh.
