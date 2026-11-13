## Ý tưởng

Duyệt xâu từ trái sang phải. Lưu $x$ là số chữ `a` đã gặp và $ans$ là số cách tạo `ab` trong tiền tố đã xét.

- Gặp `b`: cộng $x$ vào $ans$.
- Gặp `a`: tăng $x$ lên $1$.
- Các chữ khác không làm thay đổi hai giá trị.

## Tính đúng đắn

Mỗi cách tạo `ab` có đúng một vị trí cuối là chữ `b`. Khi duyệt đến vị trí ấy, mọi chữ `a` đứng trước đã được đếm trong $x$, nên cộng đúng số cách có vị trí cuối này. Các vị trí cuối khác nhau tạo ra các cách khác nhau. Vì vậy không bỏ sót và không đếm lặp cách nào.

## Độ phức tạp và cài đặt

Thời gian $O(N)$, bộ nhớ phụ $O(1)$. Đáp án có thể vượt số nguyên 32 bit; dùng số nguyên 64 bit. Cận $\binom{N}{2}$ bảo đảm kết quả nằm trong miền 64 bit.
