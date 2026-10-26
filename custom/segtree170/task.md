# SEGTREE170 — Chuyến đi vừa túi tiền

### Đề bài

Có $N$ điểm đến được đánh số từ $1$ đến $N$ theo thứ tự trên một tuyến đường. Chi phí ghé điểm $i$ là số nguyên không âm $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: sửa chi phí tại điểm $i$ thành $x$.
- `2 l B`: bắt đầu tại điểm $l$ và ghé liên tiếp các điểm $l,l+1,\ldots,r$. Tìm chỉ số cuối $r$ lớn nhất, không vượt $N$, sao cho tổng chi phí trên đoạn không vượt ngân sách $B$.

Nếu ngay điểm $l$ đã có chi phí vượt $B$, trả về $l-1$ để biểu diễn đoạn rỗng. Không được bỏ qua một điểm ở giữa chuyến đi. Các điểm có chi phí $0$ vẫn có thể được ghé dù ngân sách còn lại bằng $0$. Truy vấn không làm thay đổi chi phí.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l B`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số cuối xa nhất $r$ của chuyến đi, hoặc $l-1$ nếu không ghé được điểm nào. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le N$ và $0\le B\le10^{18}$.

### Sample Input 1

```text
6 6
2 0 3 1 0 4
2 2 3
2 1 1
2 4 1
1 3 1
2 2 3
2 6 0
```

### Sample Output 1

```text
3
0
5
5
5
```

### Sample Input 2

```text
3 4
0 0 0
2 1 0
1 2 1
2 1 0
2 3 0
```

### Sample Output 2

```text
3
1
3
```

### Giải thích

Ở ví dụ 1, từ điểm $2$ với ngân sách $3$ có thể ghé các điểm $2,3$ nhưng không thêm điểm $4$. Ngân sách $1$ không đủ ghé điểm $1$ nên trả về $0$. Từ điểm $4$ với ngân sách $1$ vẫn ghé thêm điểm $5$ có chi phí $0$. Sau khi sửa chi phí điểm $3$ thành $1$, từ điểm $2$ với ngân sách $3$ ghé được đến điểm $5$. Truy vấn cuối không ghé được điểm $6$ nên trả về $5$.

Ở ví dụ 2, khi mọi chi phí bằng $0$ thì ngân sách $0$ vẫn đi hết tuyến. Sau lần sửa, điểm $2$ cản chuyến đi bắt đầu tại điểm $1$, nhưng không ảnh hưởng chuyến đi bắt đầu tại điểm $3$.
