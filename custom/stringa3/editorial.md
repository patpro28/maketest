# STRINGA3 — Hướng dẫn giải

Duyệt xâu từ trái sang phải. Duy trì phần dư `value` của mã đang đọc và phần dư `answer` của tổng các mã đã kết thúc.

Khi gặp chữ số $d$, cập nhật $value=(10\cdot value+d)\bmod K$. Khi gặp chữ cái, cộng `value` vào `answer` theo modulo $K$, rồi đặt `value=0`. Có thể thêm một chữ cái vào cuối xâu để xử lý mã kết thúc tại ký tự cuối.

Công thức cập nhật bảo toàn phần dư của giá trị thập phân sau mỗi chữ số. Chỉ cộng mã khi gặp ranh giới nên mỗi đoạn số cực đại được tính đúng một lần. Các chữ số $0$ ở đầu và các chữ cái liên tiếp không làm sai tổng.

Độ phức tạp $O(|S|)$; bộ nhớ phụ $O(1)$ ngoài xâu đầu vào. Dùng số nguyên 64 bit cho phép nhân với $10$.

Lời giải đối chiếu duyệt từ phải sang trái, cộng đóng góp của từng chữ số theo lũy thừa của $10$ và đặt lại lũy thừa khi gặp chữ cái.

### Theo subtask

- Subtask 1 (50%): $K=1$, đáp án luôn bằng $0$.
- Subtask 2 (30%): mỗi mã hàng có giá trị không vượt $10^{12}$, có thể đọc giá trị trực tiếp vào số nguyên 64 bit, cộng các mã rồi lấy modulo $K$. Tổng không vượt $10^{17}$ vì có không quá $10^5$ mã. Số $0$ ở đầu không làm giá trị trung gian lớn hơn giá trị cuối cùng.
- Subtask 3 (20%): mã hàng có thể dài tới $10^5$ chữ số, cần tính phần dư ngay khi đọc từng chữ số.
