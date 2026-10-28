# SEGTREE115 — Hai đầu bảng thành tích

### Đề bài

Cho dãy điểm $a_1,\ldots,a_N$, có thể chứa điểm âm. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2`: tìm vị trí đầu tiên và vị trí cuối cùng đạt điểm cao nhất trong toàn dãy hiện tại.

Nếu chỉ có một vị trí đạt điểm cao nhất, in vị trí đó hai lần. Đáp án là chỉ số trong dãy, không phải giá trị điểm.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in hai chỉ số đầu tiên và cuối cùng đạt điểm cao nhất trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le a_i,x\le10^9$; $1\le i\le N$.

### Sample Input 1

```text
5 5
-2 -1 -1 -3 -1
2
1 1 0
2
1 5 0
2
```

### Sample Output 1

```text
2 5
1 1
1 5
```

### Sample Input 2

```text
1 3
-1000000000
2
1 1 -7
2
```

### Sample Output 2

```text
1 1
1 1
```

### Giải thích

Ở ví dụ 1, điểm cao nhất ban đầu là $-1$, có vị trí đầu là $2$ và cuối là $5$. Sau cập nhật đầu tiên, chỉ vị trí $1$ đạt điểm $0$. Sau cập nhật tiếp theo, vị trí $1$ và $5$ cùng đạt điểm cao nhất. Ở ví dụ 2, mọi truy vấn đều in `1 1`.
