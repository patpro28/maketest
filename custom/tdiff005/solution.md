## Ý tưởng

Tính giá trị hiện tại $A_P=\sum_{i=1}^{P}D_i$ và đặt $\Delta=X-A_P$. Cộng $\Delta$ vào $D_P$. Nếu $P<N$, trừ $\Delta$ khỏi $D_{P+1}$.

## Chứng minh tính đúng đắn

Đặt $A_0=0$. Tổng tiền tố của mảng hiệu đến $P$ bằng $A_P$. Thay $A_P$ bằng $X$ tương đương cộng $\Delta$ tại đúng vị trí $P$. Hiệu tại $P$ tăng $\Delta$ vì nó có dạng $A_P-A_{P-1}$. Nếu $P<N$, hiệu tại $P+1$ giảm $\Delta$ vì nó có dạng $A_{P+1}-A_P$. Các hiệu khác không chứa $A_P$.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Dùng số nguyên 64 bit cho tổng tiền tố, $\Delta$ và mảng hiệu mới.
