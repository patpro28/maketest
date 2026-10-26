# PREFIX12 — Hướng dẫn giải

Với mỗi chữ cái $c$, tính $P_c(i)$ là số lần xuất hiện của $c$ trong $i$ ký tự đầu. Truy vấn trả về $P_c(R)-P_c(L-1)$.

Tính đúng đắn: Các ký tự trước vị trí L bị trừ đi, các ký tự từ L đến R được giữ lại. Chỉ những ký tự bằng c đóng góp vào tổng.

Thời gian: $O(26N+Q)$. Bộ nhớ: $O(26N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
