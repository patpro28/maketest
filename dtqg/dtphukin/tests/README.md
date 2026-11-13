# Kiểm thử DTPHUKIN

Chạy từ thư mục gốc bằng `python3 dtqg/dtphukin/tests/check.py`. Thêm `--update-hashes` khi chủ động thay đổi bộ test.

Bộ chấm có hai ví dụ và 14 tệp sinh với seed cố định. Các ca lớn bao phủ mảng toàn $0$, mảng toàn $1$, khoảng cách giữa hai số $1$ quanh ngưỡng $2$, một cặp duy nhất ở các vị trí khác nhau và nhiều bộ test đạt đồng thời hai giới hạn $T$ và tổng $N$. Mảng toàn $1$ dài $200\,000$ có đáp án $20\,000\,100\,000$, kiểm tra việc dùng số nguyên 64 bit.

Lời giải đối chiếu thử trực tiếp các phép biến đổi làm đổi ít nhất một số $0$ thành $1$. Lời giải tham chiếu được so sánh với cách này trên toàn bộ 2.046 mảng nhị phân có độ dài từ $1$ đến $10$. Quy trình cũng kiểm tra hai ví dụ, các đáp án lớn tính được trực tiếp, đầu vào sai, đầu ra sai và mã băm. Mỗi lần chạy lời giải có giới hạn 1 giây.
