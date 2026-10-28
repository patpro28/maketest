# SEGTREE103 — Giá trị phổ biến nhất

### Đề bài

Một đa tập chỉ chứa các số nguyên từ $1$ đến $M$. Ban đầu, giá trị $x$ xuất hiện $f_x$ lần. Thực hiện các thao tác:

- `1 x`: thêm một lần xuất hiện của $x$.
- `2 x`: xóa một lần xuất hiện của $x$. Bảo đảm $x$ đang có trong đa tập.
- `3`: tìm giá trị xuất hiện nhiều lần nhất. Nếu có nhiều giá trị cùng tần suất lớn nhất, chọn giá trị nhỏ nhất. Nếu đa tập rỗng, in `-1`.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $M,Q$.
- Dòng thứ hai chứa $M$ số nguyên $f_1,\ldots,f_M$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `3`, in giá trị được chọn hoặc `-1` trên một dòng. Các thao tác loại `1`, `2` không tạo đầu ra.

### Ràng buộc

- $1\le M,Q\le200000$.
- $0\le f_x\le10^9$; đây là tần suất ban đầu.
- $1\le x\le M$; mọi thao tác xóa đều hợp lệ.

### Sample Input 1

```text
4 7
0 2 2 1
3
1 3
3
2 3
3
2 2
3
```

### Sample Output 1

```text
2
3
2
3
```

### Sample Input 2

```text
1 5
0
3
1 1
3
2 1
3
```

### Sample Output 2

```text
-1
1
-1
```

### Giải thích

Ở ví dụ 1, ban đầu giá trị $2$ và $3$ cùng xuất hiện hai lần nên chọn $2$. Thêm một số $3$ khiến đáp án thành $3$; xóa bớt số $3$ đưa đáp án về $2$. Sau khi xóa một số $2$, giá trị $3$ lại phổ biến nhất. Ở ví dụ 2, các đáp án lần lượt là $-1,1,-1$.
