# SEGTREE129 — Cặp thi đấu thứ k

### Đề bài

Có $N$ câu lạc bộ được đánh số từ $1$ đến $N$. Câu lạc bộ $i$ hiện có $c_i$ thành viên, mang các số $1,2,\dots,c_i$; khi $c_i=0$ thì câu lạc bộ không có thành viên.

Mỗi cặp thành viên khác nhau trong cùng câu lạc bộ tạo thành một trận đấu. Biểu diễn trận đấu bởi bộ ba $(i,u,v)$, với $1\le u<v\le c_i$. Sắp tất cả các trận tăng dần theo $i$; các trận cùng câu lạc bộ được sắp tăng dần theo $u$, rồi theo $v$.

Thực hiện $Q$ thao tác:

- `1 i x`: thay số thành viên của câu lạc bộ $i$ bằng $x$. Các thành viên của câu lạc bộ này sau cập nhật được đánh số lại từ $1$ đến $x$.
- `2 k`: tìm trận đấu thứ $k$ trong danh sách hiện tại, đánh số từ $1$. Nếu hiện có ít hơn $k$ trận thì trả lời $-1$.

Truy vấn không tổ chức hay xóa trận đấu; danh sách được xác định hoàn toàn bởi các số thành viên hiện tại.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $c_1,c_2,\dots,c_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in ba số nguyên $i,u,v$ của trận đấu được hỏi trên một dòng. Nếu không có trận đó, chỉ in $-1$ trên dòng tương ứng.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $0\le c_i\le10^4$.
- Với thao tác loại `1`: $1\le i\le N$, $0\le x\le10^4$.
- Với thao tác loại `2`: $1\le k\le10^{18}$.

### Sample Input 1

```text
3 8
3 1 2
2 1
2 3
2 4
2 5
1 2 3
2 4
2 6
2 7
```

### Sample Output 1

```text
1 1 2
1 2 3
3 1 2
-1
2 1 2
2 2 3
3 1 2
```

### Sample Input 2

```text
2 6
0 1
2 1
1 1 4
2 4
2 6
1 1 1
2 1
```

### Sample Output 2

```text
-1
1 2 3
1 3 4
-1
```

### Giải thích

Ở ví dụ 1, danh sách ban đầu là $(1,1,2)$, $(1,1,3)$, $(1,2,3)$, $(3,1,2)$; không có trận thứ năm. Sau khi đặt $c_2=3$, ba trận của câu lạc bộ $2$ được chèn giữa các trận của câu lạc bộ $1$ và $3$. Trận thứ tư là $(2,1,2)$, thứ sáu là $(2,2,3)$, thứ bảy là $(3,1,2)$.

Ở ví dụ 2, ban đầu không có trận nào. Khi câu lạc bộ $1$ có bốn thành viên, các cặp theo thứ tự là $(1,2),(1,3),(1,4),(2,3),(2,4),(3,4)$, nên trận thứ tư có hai thành viên $2,3$ và trận thứ sáu có hai thành viên $3,4$. Sau cập nhật cuối, lại không có trận nào.
