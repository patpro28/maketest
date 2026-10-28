# SEGTREE124 — Giá trị phân biệt thứ k

### Đề bài

Một đa tập chỉ chứa các số nguyên từ $1$ đến $M$. Ban đầu, giá trị $x$ xuất hiện $f_x$ lần. Thực hiện các thao tác:

- `1 x`: thêm một lần xuất hiện của $x$.
- `2 x`: xóa một lần xuất hiện của $x$. Bảo đảm $x$ đang có trong đa tập.
- `3 k`: sắp các **giá trị phân biệt** đang có theo thứ tự tăng dần, in giá trị thứ $k$. Nếu có ít hơn $k$ giá trị phân biệt, in `-1`.

Mỗi giá trị chỉ được tính một lần trong truy vấn, dù xuất hiện nhiều lần trong đa tập.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $M,Q$.
- Dòng thứ hai chứa $M$ số nguyên $f_1,\ldots,f_M$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `3`, in đáp án trên một dòng. Các thao tác loại `1`, `2` không tạo đầu ra.

### Ràng buộc

- $1\le M,Q\le200000$.
- $0\le f_x\le10^9$; đây là tần suất ban đầu.
- $1\le x,k\le M$; mọi thao tác xóa đều hợp lệ.

### Sample Input 1

```text
5 8
0 3 0 1 2
3 2
2 2
3 1
2 4
3 2
1 1
3 1
3 4
```

### Sample Output 1

```text
4
2
5
1
-1
```

### Sample Input 2

```text
1 5
0
3 1
1 1
1 1
2 1
3 1
```

### Sample Output 2

```text
-1
1
```

### Giải thích

Ở ví dụ 1, các giá trị phân biệt ban đầu là $2,4,5$, nên giá trị thứ hai là $4$. Xóa bớt một số $2$ không làm mất giá trị này. Xóa số $4$ duy nhất làm các giá trị còn lại thành $2,5$. Sau khi thêm số $1$, danh sách là $1,2,5$, không có giá trị thứ tư. Ở ví dụ 2, các truy vấn trả về $-1$ rồi $1$ vì vẫn còn một số $1$.
