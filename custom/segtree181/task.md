# SEGTREE181 — Đủ kinh phí và nhân lực

### Đề bài

Có $N$ địa điểm theo thứ tự. Địa điểm $i$ có kinh phí $a_i\ge0$ và dấu hiệu $b_i\in\{0,1\}$ cho biết có nhân sự chuyên môn hay không. Thực hiện các thao tác:

- `1 i x y`: đồng thời gán $a_i=x$ và $b_i=y$.
- `2 l S K`: tìm vị trí nhỏ nhất $r\in[l,N]$ sao cho $\sum_{i=l}^{r}a_i\ge S$ và $\sum_{i=l}^{r}b_i\ge K$. Nếu không có, in `-1`.

Cả hai điều kiện phải được thỏa mãn trên cùng đoạn $[l,r]$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Dòng thứ ba chứa $N$ số nguyên $b_1,\ldots,b_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le a_i,x\le10^9$; $b_i,y\in\{0,1\}$.
- $1\le i,l\le N$; $1\le S\le10^{18}$; $1\le K\le N$.

### Sample Input 1

```text
5 6
2 0 5 1 4
1 0 0 1 1
2 1 6 2
2 2 5 2
2 4 6 1
1 3 6 1
2 2 6 1
2 5 1 2
```

### Sample Output 1

```text
4
5
-1
3
-1
```

### Sample Input 2

```text
1 4
0
0
2 1 1 1
1 1 1000000000 1
2 1 1000000000 1
2 1 1000000000000000000 1
```

### Sample Output 2

```text
-1
1
-1
```

### Giải thích

Ở ví dụ 1, truy vấn đầu cần đến vị trí $4$ để có đủ hai địa điểm có chuyên môn. Truy vấn thứ hai cần đến vị trí $5$. Truy vấn thứ ba thiếu kinh phí dù đã đến cuối dãy. Sau cập nhật, riêng vị trí $3$ đã đủ cả hai ngưỡng cho truy vấn bắt đầu từ $2$. Truy vấn cuối thiếu nhân lực. Ở ví dụ 2, các đáp án là $-1,1,-1$.
