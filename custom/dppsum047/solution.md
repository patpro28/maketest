Tính tổng tiền tố $P_0=0$, $P_i=P_{i-1}+A_i$. Đoạn dài đúng $K$ kết thúc tại $R$ có tổng $P_R-P_{R-K}$ và bắt đầu ở $R-K+1$.

Khởi tạo kết quả bằng tổng đoạn đầu tiên $P_K$, không khởi tạo bằng $0$. Duyệt các đoạn tiếp theo theo thứ tự vị trí bắt đầu tăng dần. Khi gặp tổng lớn hơn kết quả đang giữ, cập nhật kết quả. Khởi tạo số lượng bằng $1$. Khi gặp tổng tốt hơn, đặt lại số lượng bằng $1$; khi tổng bằng kết quả đang giữ, tăng số lượng thêm $1$.

Tính đúng đắn: Mỗi đoạn dài đúng $K$ có duy nhất một đầu phải từ $K$ đến $N$, nên được xét đúng một lần. Sau khi xét đoạn đầu tiên, kết quả đang giữ là tổng lớn nhất trong những đoạn đã xét. Mỗi bước cập nhật khi và chỉ khi gặp tổng tốt hơn, nên tính chất đó tiếp tục đúng. Cuối vòng lặp, kết quả là tổng lớn nhất của mọi đoạn. Bộ đếm được đặt lại khi xuất hiện tổng tốt hơn và chỉ tăng khi gặp tổng bằng kết quả tốt nhất hiện tại, nên cuối cùng đếm đúng mọi đoạn tối ưu.

Thời gian $O(N)$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit cho các tổng vì trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$. Số lượng đoạn tối ưu và vị trí bắt đầu không vượt quá $N$.
