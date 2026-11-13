## Ý tưởng

Cộng $X$ vào $D_L$, giữ nguyên các phần tử khác của mảng hiệu.

## Chứng minh tính đúng đắn

Đặt $A_0=0$. Với $i<L$, cả $A_i$ lẫn $A_{i-1}$ giữ nguyên. Với $i>L$, cả hai cùng tăng $X$ nên hiệu giữ nguyên. Tại $i=L$, chỉ $A_i$ tăng $X$, nên $D_L$ tăng đúng $X$.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Chỉ xuất các chỉ số từ $1$ đến $N$. Dùng số nguyên 64 bit cho mảng hiệu.
