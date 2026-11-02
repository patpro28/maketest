Kiểm tra $A_i<0$, không dùng $A_i\le0$.

Đặt $B_i=1$ nếu $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính tổng tiền tố $P_0=0$, $P_i=P_{i-1}+B_i$. Số phần tử thỏa điều kiện của đoạn dài đúng $K$ kết thúc tại $R$ là $P_R-P_{R-K}$.

Khởi tạo số lượng tốt nhất bằng $P_K$, vị trí bằng $1$. Duyệt $R$ từ $K+1$ đến $N$. Chỉ khi số lượng của đoạn hiện tại lớn hơn kết quả đang giữ mới cập nhật số lượng và vị trí $R-K+1$. Khi bằng nhau, giữ nguyên vị trí để chọn đoạn xuất hiện sớm nhất.

Tính đúng đắn: mảng đánh dấu cho mỗi phần tử thỏa điều kiện đúng một đơn vị, nên hiệu hai tổng tiền tố đếm chính xác số lượng trong đoạn. Mỗi đoạn dài đúng $K$ được xét đúng một lần theo thứ tự vị trí bắt đầu tăng dần. Cập nhật khi số lượng lớn hơn giữ đúng giá trị tối ưu; không cập nhật khi bằng nhau giữ đúng vị trí nhỏ nhất. Do đó hai kết quả cuối cùng thỏa yêu cầu. Nếu mọi số lượng đều bằng $0$, vị trí khởi tạo $1$ được giữ nguyên.

Thời gian $O(N)$, bộ nhớ $O(N)$. Các bộ đếm không vượt quá $N$.
