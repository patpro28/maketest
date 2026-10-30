# PREFIX07 — Hướng dẫn giải

Tính tổng tiền tố $S$. Với đầu phải $r\ge K$, đầu trái phải thỏa $l-1\le r-K$. Duy trì min của $S_0,\ldots,S_{r-K}$ và cập nhật đáp án bằng $S_r$ trừ min này. Trước khi xét $r$, đưa $S_{r-K}$ vào min. Khởi tạo đáp án bằng âm vô cùng.

Tính đúng đắn: Với mỗi đầu phải, tập tiền tố được duy trì trùng với toàn bộ đầu trái hợp lệ. Trừ tiền tố nhỏ nhất cho tổng lớn nhất; lấy max qua các đầu phải cho đáp án toàn cục.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(N)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
