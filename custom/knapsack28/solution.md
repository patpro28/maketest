# Lời giải — Xây số lớn nhất chia hết

Với số dương không có số $0$ ở đầu, ưu tiên độ dài rồi thứ tự từ trái sang phải. Dùng `f[b][r]` là độ dài lớn nhất của phần có thể viết **thêm**, tốn đúng $b$ đồng, khi tiền tố hiện tại có dư $r$, để kết thúc với dư $0$.

Khởi tạo `f[0][0]=0`, các trạng thái còn lại không đạt được. Nếu viết chữ số $d$, dư mới là $(10r+d)\bmod M$, nên chuyển từ `f[b-C_d][dư mới]+1`. Duyệt ngân sách tăng vì chi phí dương. Trạng thái này cho phép số $0$ đầu hậu tố, phù hợp khi đã có tiền tố.

Thử riêng chữ số đầu $1,\ldots,9$ để tìm độ dài hợp lệ lớn nhất. Nếu không có số dương, chỉ số `0` hợp lệ khi $B=C_0$. Với độ dài tối ưu, truy vết từ trái sang phải: thử chữ số giảm dần và giữ chữ số cho phép hậu tố đạt đúng số vị trí còn lại.

Phép chuyển liệt kê mọi hậu tố và đảm bảo trạng thái cuối đúng dư $0$. Chọn chữ số lớn nhất vẫn hoàn thành được giữ tiền tố lớn nhất, nên cho số tối ưu trong độ dài lớn nhất. Không cần thêm chiều độ dài cho số dư vì DP được định nghĩa theo dư của **tiền tố hiện tại**, không phải dư của một hậu tố đứng độc lập.

Thời gian $O(10BM)$, bộ nhớ $O(BM)$ và chuỗi đáp án. Độ dài không vượt $B$; không lưu đáp án trong kiểu số nguyên cố định.
