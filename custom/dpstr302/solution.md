## Trạng thái và chuyển

Lưu $x,y,z$ là số cách tạo `a`, `ab`, `aba` trong tiền tố đã xét, ban đầu bằng $0$.

- Gặp `a`: cập nhật **$z\leftarrow z+y$ trước**, rồi mới $x\leftarrow x+1$.
- Gặp `b`: cập nhật $y\leftarrow y+x$.
- Các chữ khác không thay đổi trạng thái.

Cũng có thể dùng mảng $f[0\ldots3]$ cho mẫu `aba`, với $f[0]=1$, rồi duyệt chỉ số mẫu giảm dần cho mỗi ký tự nguồn.

## Tính đúng đắn

Các cách mới tạo `aba` phải kết thúc ở chữ `a` hiện tại và có phần trước là một cách tạo `ab` hoàn toàn nằm bên trái. Mỗi cách như vậy mở rộng được duy nhất một lần. Cập nhật theo tiền tố mẫu giảm dần giữ các giá trị dùng để mở rộng thuộc tiền tố nguồn cũ, nên cùng một vị trí không bị dùng hai lần. Phân loại theo việc dùng vị trí hiện tại hay không cho thấy mọi cách đều được đếm đúng một lần.

## Độ phức tạp và cài đặt

Thời gian $O(N)$, bộ nhớ phụ $O(1)$. Dùng số nguyên 64 bit; đáp án không quá $\binom{200000}{3}<1.34\cdot10^{15}$.
