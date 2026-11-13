## Thuật toán

Đặt $B_i=A_iW_i$. Vì hệ số $W_i$ cố định, gán số đo $A_i=x$ chỉ làm thay đổi $B_i$ thành $xW_i$. Dựng segment tree lưu tổng trên dãy $B$.

- Với thao tác gán, thay giá trị ở lá $i$ bằng $xW_i$ và tính lại tổng của các nút tổ tiên.
- Với truy vấn $[l,r]$, lấy tổng của đoạn $[l,r]$ trên cây.

## Chứng minh tính đúng đắn

Lúc dựng cây, mỗi lá $i$ lưu đúng đóng góp $A_iW_i$. Cập nhật số đo chỉ đổi đóng góp của thiết bị tương ứng, nên phép gán tại lá duy trì tính chất đó. Mỗi nút trong là tổng hai nút con, do vậy nó lưu đúng tổng đóng góp của đoạn được quản lý.

Truy vấn lấy tổng các nút có đoạn đôi một rời nhau và phủ đúng $[l,r]$. Kết quả là $\sum_{i=l}^r A_iW_i$ theo yêu cầu.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác tốn $O(log(N+1))$ thời gian. Bộ nhớ là $O(N)$.

Mỗi tích có trị tuyệt đối tối đa $10^{13}$, còn mỗi tổng có trị tuyệt đối tối đa $2\cdot10^{18}$. Cần dùng số nguyên 64 bit ngay khi nhân.
