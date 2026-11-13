## Tách phần còn lại

Sau khi bỏ qua $[u,v]$ trong đoạn $[l,r]$, các trạm được xét thuộc hai đoạn $[l,u-1]$ và $[v+1,r]$. Hai đoạn rời nhau. Đoạn bên trái khác rỗng khi $l<u$, còn đoạn bên phải khác rỗng khi $v<r$.

Dựng cây đoạn lưu giá trị lớn nhất. Lá tại vị trí $i$ chứa $A_i$. Nút cha là max của hai nút con. Khi gán $A_i=x$, cập nhật lá rồi tính lại các nút trên đường đến gốc.

## Tính đúng đắn

Các nút được chọn trong một truy vấn đoạn phủ đúng đoạn đó, nên giá trị lớn nhất trong các nút là giá trị lớn nhất của đoạn. Mỗi truy vấn của bài lấy max ở từng phần còn lại khác rỗng rồi lấy giá trị lớn nhất trong các kết quả. Mọi trạm hợp lệ nằm ở đúng một trong các phần này, nên giá trị thu được là đáp án.

Nếu cài đặt bằng cách khởi tạo đáp án trước khi ghép, dùng một giá trị nhỏ hơn mọi $A_i$. Giá trị lớn nhất của phần còn lại có thể âm.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi lần gán cập nhật một lá. Mỗi truy vấn dùng tối đa hai truy vấn max. Thời gian cho mỗi thao tác là $O(\log(N+1))$ và bộ nhớ là $O(N)$.
