## Ý tưởng

Cộng $X$ vào $D_L$. Nếu $R<N$, trừ $X$ khỏi $D_{R+1}$. In mảng hiệu đã cập nhật.

## Chứng minh tính đúng đắn

Đặt $A_0=0$. Ở hai vị trí kề nhau cùng thuộc đoạn hoặc cùng ở ngoài đoạn, lượng thay đổi triệt tiêu khi lấy hiệu. Ở vị trí $L$, phần tử hiện tại tăng $X$ còn phần tử trước giữ nguyên, nên hiệu tăng $X$. Ở vị trí $R+1$ nếu tồn tại, phần tử trước tăng $X$ còn phần tử hiện tại giữ nguyên, nên hiệu giảm $X$.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Khi $R=N$, không cần ghi phần tử $D_{N+1}$. Dùng số nguyên 64 bit cho mảng hiệu.
