## Trạng thái và chuyển

Lưu $x,y,z$ lần lượt là số cách tạo `a`, `ab`, `abc` trong tiền tố đã xét. Ban đầu đều bằng $0$.

- Gặp `c`: $z\leftarrow z+y$.
- Gặp `b`: $y\leftarrow y+x$.
- Gặp `a`: $x\leftarrow x+1$.

Các chữ khác được bỏ qua. Kết quả là $z$ sau khi duyệt hết xâu.

## Tính đúng đắn

Khi gặp một chữ `b`, mỗi cách tạo `a` trước đó mở rộng thành đúng một cách tạo `ab` có vị trí cuối tại đây. Tương tự, chữ `c` mở rộng từng cách tạo `ab` trước nó thành `abc`. Phân loại theo vị trí cuối cho thấy các cách mới và các cách cũ không giao nhau, đồng thời mọi cách hợp lệ đều được tạo ra. Do đó ba biến luôn đếm đúng các mẫu tương ứng trong tiền tố.

## Độ phức tạp và cài đặt

Thời gian $O(N)$, bộ nhớ phụ $O(1)$. Dùng số nguyên 64 bit vì kết quả có thể vượt 32 bit. Đáp án không quá $\binom{200000}{3}<1.34\cdot10^{15}$.
