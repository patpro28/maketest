# SEGTREE127 — Số còn thiếu thứ k

### Đề bài

Quản lý một đa tập gồm các số nguyên trong $[1,M]$. Ban đầu, số $x$ xuất hiện $f_x$ lần. Một giá trị được gọi là **còn thiếu** nếu hiện không xuất hiện lần nào trong đa tập.

Thực hiện $Q$ thao tác:

- `1 x`: thêm một lần xuất hiện của số $x$.
- `2 x`: xóa một lần xuất hiện của số $x$. Dữ liệu bảo đảm số $x$ đang xuất hiện ít nhất một lần.
- `3 k`: xét các giá trị còn thiếu thuộc $[1,M]$ theo thứ tự tăng dần và tìm giá trị thứ $k$. Nếu có ít hơn $k$ giá trị còn thiếu thì trả lời $-1$.

Chỉ xét các số trong $[1,M]$; các số ngoài miền này không tham gia truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $M,Q$.
- Dòng thứ hai chứa $M$ số nguyên $f_1,f_2,\dots,f_M$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `3`, in giá trị còn thiếu thứ $k$ hoặc $-1$ nếu không đủ giá trị.

### Ràng buộc

- $1\le M,Q\le2\cdot10^5$.
- $0\le f_x\le10^9$ ở thời điểm ban đầu.
- Với thao tác loại `1` hoặc `2`: $1\le x\le M$.
- Với thao tác loại `3`: $1\le k\le M$.
- Mọi thao tác xóa đều hợp lệ. Tần suất sau các thao tác có thể lớn hơn $10^9$.

### Sample Input 1

```text
6 10
0 2 0 1 0 0
3 3
1 3
3 2
2 2
3 2
2 2
3 2
1 1
3 4
3 1
```

### Sample Output 1

```text
5
5
5
2
-1
2
```

### Sample Input 2

```text
1 7
0
3 1
1 1
1 1
2 1
3 1
2 1
3 1
```

### Sample Output 2

```text
1
-1
1
```

### Giải thích

Ở ví dụ 1, các số còn thiếu ban đầu là $1,3,5,6$, nên số thứ ba là $5$. Thêm số $3$ làm danh sách còn $1,5,6$. Xóa một bản sao của số $2$ chưa làm số $2$ trở thành còn thiếu; sau lần xóa thứ hai, danh sách là $1,2,5,6$. Cuối cùng thêm số $1$ làm danh sách còn $2,5,6$, nên không có số thứ tư và số thứ nhất là $2$.

Ở ví dụ 2, sau khi thêm hai lần rồi xóa một lần, số $1$ vẫn còn xuất hiện, nên truy vấn giữa trả lời $-1$. Xóa bản sao cuối cùng khiến số $1$ lại trở thành còn thiếu.
