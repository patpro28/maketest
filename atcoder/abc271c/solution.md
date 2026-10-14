# Hướng dẫn giải

Kết quả không vượt quá $N$ vì mỗi thao tác đổi làm giảm số sách.

Xét việc đọc đến tập $k$. Gọi $c$ là số tập phân biệt trong đoạn $[1,k]$ đã có. Giữ lại một cuốn cho mỗi tập này, còn $N-c$ cuốn có thể đem đổi. Cần mua $k-c$ tập còn thiếu, mỗi tập tốn hai cuốn, nên điều kiện cần và đủ là:

$$2(k-c) \leq N-c.$$

Điều kiện là cần thiết: ban đầu thiếu $k-c$ tập, mỗi tập phải được mua qua ít nhất một thao tác. Sau ít nhất $k-c$ thao tác, số sách còn lại tối đa là $N-(k-c)$ và phải đủ $k$ cuốn. Điều kiện là đủ bằng cách dùng $2(k-c)$ cuốn dư để mua đúng các tập thiếu, trước khi đọc.

Đánh dấu các tập không vượt quá $N$, rồi duyệt $k$ từ $1$ đến $N$, cập nhật $c$ và kiểm tra bất đẳng thức. Khi điều kiện sai có thể dừng: đại lượng $2k-c$ tăng ít nhất một sau mỗi bước.

Độ phức tạp: $O(N)$ thời gian và $O(N)$ bộ nhớ.

Lời giải đối chiếu `greedy.cpp` sắp xếp các tập, giữ một bản mỗi tập và đếm sách trùng làm sách dư. Lần lượt lấy tập nhỏ nhất cần đọc; nếu thiếu, dùng sách dư và các tập lớn nhất còn lại để đổi. Độ phức tạp $O(N\log N)$.
