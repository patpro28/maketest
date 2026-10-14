# Lời giải — Mua vé đạt đủ điểm

Dùng `dp[p]` là chi phí ít nhất để đạt tổng điểm đã chặn ở $X$: chỉ số $p<X$ biểu diễn đúng $p$ điểm, còn $p=X$ biểu diễn ít nhất $X$ điểm.

Khởi tạo `dp[0]=0`, các trạng thái khác vô cùng. Khi xét vé $(C_i,P_i)$, có thể bỏ qua vé hoặc mua vé để chuyển từ $p$ đến $\min(X,p+P_i)$ với chi phí cộng $C_i$. Duyệt $p$ giảm để không mua một vé nhiều lần. Chuyển từ $X$ đến chính $X$ không cải thiện đáp án vì giá vé dương.

Mọi tổng điểm từ $X$ trở lên có cùng khả năng đáp ứng yêu cầu và các vé sau đều có điểm dương, nên chỉ giữ chi phí ít nhất của chúng là đủ. Bất biến về chi phí nhỏ nhất được bảo toàn qua hai lựa chọn bỏ/mua; `dp[X]` là kết quả, hoặc `-1` nếu không đạt được.

Thời gian $O(NX)$, bộ nhớ $O(X)$. Tổng chi phí có thể tới $2\cdot10^{11}$, phải dùng số nguyên 64 bit.

## Kiểm thử

35 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 9 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Ba test bổ sung đều có $N=200$, $X=20000$: `max_06` có mọi $P_i=20000$, tổng điểm bằng $4000000$; `max_07` có mọi $P_i=19999$, tổng điểm bằng $3999800$ và cần ít nhất hai vé; `max_08` trộn điểm gần $20000$, trong đó mua hai vé rẻ đạt đủ điểm với chi phí $3$, tốt hơn một vé $20000$ điểm giá $10^9$. Các test này kiểm tra việc chặn tổng điểm ở $X$ và phân biệt yêu cầu "ít nhất" với "đúng bằng".

Chạy `python3 custom/knapsack13/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
