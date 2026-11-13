## Ý tưởng

Giữ tổng $S$ ban đầu bằng $0$. Khi đọc $D_i$, cộng nó vào $S$ và in $S$.

## Chứng minh tính đúng đắn

Tổng $D_1+D_2+\cdots+D_i$ bằng $A_1+(A_2-A_1)+\cdots+(A_i-A_{i-1})=A_i$. Vì $S$ bằng tổng này sau khi đọc $D_i$, mỗi giá trị in ra là phần tử đúng của dãy.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Tổng tích lũy có thể đạt trị tuyệt đối $2\cdot10^{14}$. Dùng số nguyên 64 bit.
