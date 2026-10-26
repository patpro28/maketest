# SEGTREE192 — Bãi đỗ xe vòng tròn

### Đề bài

Có $N$ chỗ đỗ được đánh số từ $1$ đến $N$ theo vòng tròn. Ban đầu chỗ $i$ có trạng thái $b_i$: $0$ là trống, $1$ là có xe. Thực hiện các thao tác:

- `1 p`: xe đến từ vị trí $p$. Tìm chỗ trống đầu tiên theo thứ tự $p,p+1,\ldots,N,1,\ldots,p-1$. Nếu có, in số chỗ và đánh dấu chỗ đó có xe. Nếu không có, in `-1` và giữ nguyên trạng thái.
- `2 p`: làm trống chỗ $p$. Nếu chỗ này vốn đã trống, trạng thái không thay đổi.

Chỉ thao tác xe đến tạo đầu ra.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $b_1,\ldots,b_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in số chỗ được chọn hoặc `-1` trên một dòng. Thao tác loại `2` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $b_i\in\{0,1\}$; $1\le p\le N$.

### Sample Input 1

```text
5 8
1 0 1 1 0
1 4
1 5
1 1
2 3
1 4
2 3
2 3
1 3
```

### Sample Output 1

```text
5
2
-1
3
3
```

### Sample Input 2

```text
1 4
0
1 1
1 1
2 1
1 1
```

### Sample Output 2

```text
1
-1
1
```

### Giải thích

Ở ví dụ 1, xe đầu nhận chỗ $5$. Xe tiếp theo bắt đầu từ $5$ rồi đi vòng về chỗ trống $2$. Xe thứ ba không còn chỗ. Sau khi làm trống chỗ $3$, xe bắt đầu tại $4$ đi vòng và nhận chỗ $3$. Làm trống một chỗ hai lần không tạo thêm chỗ. Ở ví dụ 2, các lượt xe đến có kết quả $1,-1,1$.
