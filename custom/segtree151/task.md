# SEGTREE151 — Ngày giá giảm trở lại

### Đề bài

Cho dãy giá $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 p`: tìm vị trí nhỏ nhất $j$ sao cho $p<j\le N$ và $a_j<a_p$. Nếu không có, in `-1`.

Giá bằng $a_p$ không được xem là giảm. Mỗi truy vấn xét dãy tại thời điểm truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le a_i,x\le10^9$.
- $1\le i,p\le N$.

### Sample Input 1

```text
5 6
5 5 7 3 4
2 1
2 3
2 5
1 2 2
2 1
2 2
```

### Sample Output 1

```text
4
4
-1
2
-1
```

### Sample Input 2

```text
1 3
0
2 1
1 1 1000000000
2 1
```

### Sample Output 2

```text
-1
-1
```

### Giải thích

Ở ví dụ 1, từ vị trí $1$ và $3$, lần giảm giá đầu tiên đều ở vị trí $4$. Vị trí $5$ không còn ngày phía sau. Sau khi giá ở vị trí $2$ bằng $2$, truy vấn từ vị trí $1$ trả về $2$, còn truy vấn từ vị trí $2$ thất bại. Ở ví dụ 2, không có vị trí nào ở phía sau phần tử duy nhất.
