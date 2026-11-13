Dựng cây tiền tố của từ điển. Tại nút kết thúc một từ, lưu chi phí nhỏ nhất của các mục có từ đó. Đặt $F[i]$ là chi phí tối ưu của tiền tố dài $i$. Từ mỗi $i$ có phương án, đi trên cây theo các chữ bắt đầu ở $i+1$, dừng khi không có cạnh hoặc đã đọc hết xâu. Mỗi nút kết thúc từ cho phép cập nhật tiền tố mới bằng $F[i]$ cộng chi phí của nút.

Cây liệt kê đúng mọi từ khớp với xâu tại điểm cắt đang xét. Mỗi cách chia gồm các bước tăng độ dài tiền tố theo đúng những cạnh đó. Thay một mục bằng mục rẻ hơn có cùng nội dung luôn giữ nguyên các điểm cắt, nên chỉ cần giữ giá nhỏ nhất tại mỗi nút.

Với $T$ là tổng độ dài từ điển và $H$ là độ dài từ lớn nhất, thời gian $O(26T+NH)$ và bộ nhớ $O(26T+N)$. Dùng số nguyên 64 bit cho chi phí.
