# Lời giải — Nâng cấp robot

Trước hết cho tất cả linh kiện chạy thường, thu được $base=S+\sum A_i$. Ép xung linh kiện $i$ chỉ làm tăng thêm $D_i=B_i-A_i$. Cần chọn không quá $K$ vị trí có tổng phần tăng đúng bằng $R=X-base$.

Nếu $R<0$ hoặc $R>\sum D_i$, đáp án là `NO`. Có thể dùng trạng thái boolean `f[k][s]`: đạt tổng $s$ với đúng $k$ linh kiện ép xung.

Do chỉ cần kiểm tra số linh kiện không vượt $K$, lời giải mẫu gộp chiều số lượng: `dp[s]` là **số linh kiện ít nhất** cần ép xung để đạt tổng $s$. Khởi tạo `dp[0]=0`, các tổng khác bằng $N+1$. Với mỗi $D_i$, duyệt tổng giảm và cập nhật `dp[s]=min(dp[s],dp[s-D_i]+1)`.

Một tập ép xung tương ứng duy nhất với một tập phần tăng. Giữ số lượng ít nhất cho mỗi tổng không làm mất nghiệm, vì nó luôn có lợi hơn cho điều kiện tối đa $K$. Bất biến của quy hoạch động suy ra đáp án là `dp[R] <= K`.

Đặt $D=\sum D_i\le20000$. Thời gian $O(ND)$, bộ nhớ $O(D)$. $base$ và $X$ phải dùng số nguyên 64 bit.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack12/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
