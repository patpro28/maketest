# SEGTREE112 — Trạm cứu hộ gần nhất

### Đề bài

Có $N$ trạm nằm tại các vị trí nguyên $1,\ldots,N$ trên một tuyến đường thẳng. Trạm $i$ có trạng thái $b_i$: bằng $1$ nếu hoạt động, bằng $0$ nếu ngừng hoạt động. Thực hiện các thao tác:

- `1 i`: đảo trạng thái trạm $i$.
- `2 p`: tìm trạm hoạt động có khoảng cách chỉ số $|i-p|$ nhỏ nhất tới vị trí $p$. Nếu có nhiều trạm cùng khoảng cách, chọn trạm có chỉ số nhỏ nhất. Nếu không có trạm hoạt động, in `-1`.

Nếu trạm tại $p$ hoạt động, đáp án là chính $p$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $b_1,\ldots,b_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $b_i\in\{0,1\}$; $1\le i,p\le N$.

### Sample Input 1

```text
7 6
0 1 0 0 0 1 0
2 4
2 5
1 2
2 1
1 6
2 4
```

### Sample Output 1

```text
2
6
6
-1
```

### Sample Input 2

```text
1 4
0
2 1
1 1
2 1
1 1
```

### Sample Output 2

```text
-1
1
```

### Giải thích

Ở ví dụ 1, vị trí $4$ cách đều trạm $2$ và $6$ nên chọn $2$. Vị trí $5$ gần trạm $6$ hơn. Sau khi tắt trạm $2$, trạm $6$ là trạm hoạt động duy nhất; sau khi tắt tiếp trạm $6$, không còn đáp án. Ở ví dụ 2, hai truy vấn trả về $-1$ rồi $1$.
