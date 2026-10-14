# Lời giải — Đội trưởng phải đủ mạnh

Sắp xếp các chiến binh theo $A_i$ không giảm; khi bằng nhau, cố định một thứ tự bất kỳ. Mỗi đội không rỗng có đúng một thành viên đứng cuối theo thứ tự này. Nếu thành viên cuối là $i$, sức mạnh lớn nhất của đội bằng $A_i$.

Duy trì `dp[s]` là số tập con của các chiến binh **đã xét trước** có tổng trang bị $s$, modulo $998244353$. Khởi tạo `dp[0]=1` cho tập rỗng. Trước khi thêm chiến binh $i$ vào DP, cộng $\sum_{s=0}^{A_i-B_i}dp[s]$ vào đáp án; nếu $A_i<B_i$, không cộng gì. Sau đó cập nhật DP theo tổng giảm như bài đếm tập con.

Mỗi tập con trước $i$ có tổng không vượt $A_i-B_i$ ghép với $i$ tạo một đội hợp lệ. Ngược lại, bỏ thành viên đứng cuối khỏi một đội hợp lệ cho đúng một trạng thái được cộng. Các đội được phân loại theo thành viên cuối nên không trùng, kể cả khi nhiều $A_i$ bằng nhau. Không cộng tập rỗng vào đáp án.

Chỉ cần lưu tổng trang bị đến $M=\max A_i\le5000$: tổng lớn hơn $M$ không thể xuất hiện trong đội hợp lệ, và mọi $B_i$ đều dương. Thời gian $O(N\log N+NM)$, bộ nhớ $O(N+M)$. Hai số dư cộng lại vẫn vừa số nguyên 32 bit có dấu.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack16/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
