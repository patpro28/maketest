Đặt $P[i]$ là tổng chữ số của tiền tố dài $i$. Điểm cắt $j$ đứng trước mảnh cuối phải thuộc $[i-R,i-L]$ và thỏa $P[j]\ge P[i]-B$. Do $P$ không giảm, có thể dùng một con trỏ tăng để tìm vị trí đầu tiên thỏa bất đẳng thức. Giao hai điều kiện cho một đoạn chỉ số.

Mỗi trạng thái lưu cặp (số mảnh ít nhất, số cách tối ưu). Khi gộp hai tập điểm cắt, chọn cặp có số mảnh thấp hơn. Nếu bằng nhau, cộng số cách theo modulo. Cây đoạn lưu các cặp theo điểm cắt, bắt đầu với $(0,1)$ tại tiền tố rỗng và trạng thái không thể đạt ở các vị trí khác. Với mỗi tiền tố, truy vấn đoạn điểm cắt hợp lệ và tăng số mảnh thêm một nếu truy vấn có phương án.

Mọi cách chia có đúng một điểm cắt cuối. Chọn một cách tối ưu cho tiền tố trước đó rồi nối mảnh cuối tạo một cách cho tiền tố mới. Với mỗi điểm cắt, dùng phương án kém tối ưu hơn ở phần trước không thể đạt tối ưu toàn cục. Khi nhiều điểm cắt cho cùng giá trị nhỏ nhất, các bộ điểm cắt thu được khác nhau, nên số cách được cộng.

Thời gian $O(N\log N)$ và bộ nhớ $O(N)$. Dùng trường số mảnh để nhận biết trạng thái không thể đạt vì số cách sau khi lấy dư có thể bằng $0$.
