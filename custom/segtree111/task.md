# SEGTREE111 — Chỗ đứt của dãy tăng

### Đề bài

Cho dãy số nguyên $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l r`: tìm vị trí nhỏ nhất $i$ thỏa mãn $l\le i<r$ và $a_i>a_{i+1}$. Nếu không có vị trí như vậy, in `-1`.

Vị trí được in là chỉ số trong dãy ban đầu. Đặc biệt, truy vấn có $l=r$ luôn có đáp án `-1`.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le a_i,x\le10^9$.
- $1\le i\le N$; $1\le l\le r\le N$.

### Sample Input 1

```text
5 5
1 3 2 2 4
2 1 5
1 3 3
2 2 4
1 4 3
2 1 5
```

### Sample Output 1

```text
2
3
-1
```

### Sample Input 2

```text
1 3
0
2 1 1
1 1 -1
2 1 1
```

### Sample Output 2

```text
-1
-1
```

### Giải thích

Ở ví dụ 1, chỗ giảm đầu tiên ban đầu là giữa vị trí $2$ và $3$. Sau cập nhật đầu tiên, chỗ giảm nằm giữa vị trí $3$ và $4$. Sau cập nhật thứ hai, dãy không giảm. Ở ví dụ 2, dãy chỉ có một phần tử nên không có cặp kề nhau để xét.
