# PREFIX09 — Hướng dẫn giải

Đặt $C_i=A_i-B_i$, nhân đôi dãy và tính tổng tiền tố $S$. Xuất phát từ $s$ hợp lệ khi và chỉ khi $S_j\ge S_{s-1}$ với mọi $j$ trong $[s,s+N-1]$. Vì thế cần lấy min trên từng cửa sổ độ dài $N$ của dãy tổng tiền tố. Dùng deque lưu các chỉ số có giá trị $S$ tăng dần: bỏ chỉ số hết hạn ở đầu và bỏ các giá trị không nhỏ hơn giá trị mới ở cuối. Mỗi chỉ số được thêm và bỏ nhiều nhất một lần. Khi tổng $C_i$ âm, không có trạm hợp lệ; điều kiện cửa sổ cũng tự loại trường hợp này.

Tính đúng đắn: Hiệu tổng tiền tố biểu diễn lượng nhiên liệu sau mỗi chặng. Điều kiện min cửa sổ tương đương mọi chặng đều không âm. Deque giữ đúng min vì chỉ loại chỉ số hết hạn hoặc bị chỉ số mới tốt hơn thay thế.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(N)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
