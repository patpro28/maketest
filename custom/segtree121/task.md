# SEGTREE121 — Món hàng thứ k theo giá

### Đề bài

Có $M$ mức giá nguyên từ $1$ đến $M$. Ban đầu có $c_p$ món hàng giá $p$. Các món cùng mức giá được tính là những món riêng biệt. Thực hiện các thao tác:

- `1 p x`: nhập thêm $x$ món hàng giá $p$.
- `2 k`: xếp toàn bộ hàng đang có theo giá không giảm, tìm món thứ $k$. Nếu tồn tại, in giá của món đó và bán đúng một món ở mức giá này. Nếu có ít hơn $k$ món, in `-1` và không thay đổi tồn kho.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $M,Q$.
- Dòng thứ hai chứa $M$ số nguyên $c_1,\ldots,c_M$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le M,Q\le200000$.
- $0\le c_p\le10^9$.
- $1\le p\le M$; $1\le x\le10^9$; $1\le k\le10^{18}$.

### Sample Input 1

```text
4 6
0 2 1 0
2 2
2 2
2 2
1 1 3
2 3
2 3
```

### Sample Output 1

```text
2
3
-1
1
2
```

### Sample Input 2

```text
1 5
0
2 1
1 1 1000000000
2 1000000000
2 1000000000
2 999999999
```

### Sample Output 2

```text
-1
1
-1
1
```

### Giải thích

Ở ví dụ 1, hai lần bán đầu có giá lần lượt là $2$ và $3$. Lần bán tiếp theo thất bại vì chỉ còn một món. Sau khi nhập ba món giá $1$, món thứ ba có giá $1$; sau khi bán món này, món thứ ba có giá $2$. Ở ví dụ 2, lần bán đầu thất bại; sau khi nhập hàng, các lần bán thành công đều có giá $1$.
