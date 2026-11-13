Tính $C[l][r]$, số cặp gương khác nhau trong đoạn. Với đoạn dài ít nhất hai, lấy giá trị đoạn trong rồi cộng $1$ nếu hai đầu khác nhau. Mỗi cặp khác nhau phải đổi ít nhất một chữ và đổi một chữ là đủ. Các cặp không chung vị trí, nên $C$ cũng là chi phí sửa nhỏ nhất.

Đặt $F_t[i]$ là chi phí nhỏ nhất để chia tiền tố dài $i$ thành $t$ mảnh. Thử điểm cắt cuối $j<i$, dùng $F_{t-1}[j]+C[j+1][i]$. Khởi tạo chỉ $F_0[0]=0$, các trạng thái còn lại của lớp $0$ bằng vô cực. Mọi cách chia có đúng một điểm cắt trước mảnh cuối và chi phí sửa mảnh đó độc lập với phần trước. Do đó phép lấy nhỏ nhất xét đủ và chỉ xét phương án hợp lệ.

Thời gian $O(KN^2)$, với nhiều nhất $K\cdot N(N+1)/2$ lượt thử cắt và $O(N^2)$ tiền xử lý. Bộ nhớ $O(N^2)$ sau khi nén lớp số mảnh.
