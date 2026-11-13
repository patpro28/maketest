## Ý tưởng

Cộng $X$ vào $D_L$ và, nếu $R<N$, trừ $X$ khỏi $D_{R+1}$. Duyệt mảng hiệu đã cập nhật, cộng dồn từ trái sang phải để thu được dãy mới.

## Chứng minh tính đúng đắn

Đặt $A_0=0$. Khi cộng $X$ vào $[L,R]$, hiệu giữa hai vị trí kề nhau chỉ đổi khi đúng một vị trí thuộc đoạn. Điều đó làm $D_L$ tăng $X$ và làm $D_{R+1}$ giảm $X$ nếu $R<N$. Sau khi sửa các hiệu, tổng tiền tố đến $i$ triệt tiêu các hạng trung gian và bằng giá trị mới của $A_i$.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Dùng số nguyên 64 bit cho cả mảng hiệu và tổng tích lũy.
