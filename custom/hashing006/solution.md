# Lời giải — HASHING006

Với một xâu $S$, mọi phép xoay của nó là một đoạn dài $m$ bắt đầu tại một trong $m$ vị trí đầu của $S+S$. Chọn phép xoay nhỏ nhất theo thứ tự từ điển làm đại diện chuẩn.

Duyệt từng vị trí ứng viên, so sánh với vị trí tốt nhất hiện có. Mỗi lần so sánh dùng hash kép và tìm kiếm nhị phân để tìm tiền tố chung, rồi xét ký tự khác đầu tiên. Nếu hai phép xoay bằng nhau thì có thể giữ vị trí cũ.

Hai xâu thuộc cùng nhóm khi và chỉ khi chúng có cùng đại diện chuẩn. Đưa hash kép của các đại diện vào một tập hợp và in kích thước tập. Độ dài mọi đại diện đều bằng $m$ nên không cần thêm độ dài vào khóa.

Đặt $L=n\cdot m$. Độ phức tạp kỳ vọng $O(L\log(m+1))$, bộ nhớ $O(m+n)$. Một hướng giải khác là thuật toán Booth để chọn phép xoay nhỏ nhất trong thời gian tuyến tính.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
