## Thông tin tại mỗi nút

Mỗi nút lưu giá trị lớn nhất và giá trị lớn thứ hai phân biệt của đoạn nó quản lý. Dùng $-1$ cho mức chưa tồn tại vì các giá trị trong dãy đều không âm. Lá tại vị trí $i$ lưu $(A_i,-1)$, còn đoạn rỗng dùng $(-1,-1)$.

## Phép ghép

Gọi $(m_1,s_1)$ và $(m_2,s_2)$ là thông tin của hai đoạn con.

- Nếu $m_1=m_2$, giá trị lớn nhất của đoạn ghép là $m_1$. Mức cao thứ hai là $\max(s_1,s_2)$ vì giá trị lớn nhất bị loại khỏi cả hai đoạn.
- Nếu $m_1>m_2$, giá trị lớn nhất của đoạn ghép là $m_1$. Hai ứng viên cho mức cao thứ hai là $s_1$ và $m_2$, nên lấy $\max(s_1,m_2)$.
- Nếu $m_2>m_1$, kết quả tương ứng là $(m_2,\max(m_1,s_2))$.

Mỗi trường hợp xét giá trị lớn nhất còn lại sau khi bỏ mọi lần xuất hiện của giá trị lớn nhất chung. Vì vậy phép ghép cho đúng hai mức phân biệt cao nhất.

## Xử lý thao tác

Khi gán $A_i=x$, đặt lá thành $(x,-1)$ rồi ghép lại các nút tổ tiên. Đối với truy vấn, ghép thông tin các nút phủ đúng $[l,r]$ và in mức thứ hai. Đoạn rỗng có thể dùng khi khởi tạo kết quả ghép, vì nó không đóng góp mức giá trị nào.

## Độ phức tạp

Dựng cây trong $O(N)$. Phép ghép tốn $O(1)$, nên mỗi lần gán hoặc truy vấn mất $O(\log(N+1))$. Bộ nhớ là $O(N)$.
