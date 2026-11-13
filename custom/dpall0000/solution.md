## Ý tưởng

Gọi $D_i$ là phí nhỏ nhất để đến vị trí $i$. Đặt $D_0=0$ và $D_1=A_1$. Với $i\ge2$, bước cuối chỉ có thể xuất phát từ vị trí $i-1$ hoặc $i-2$, nên
$$
D_i=A_i+\min(D_{i-1},D_{i-2}).
$$
Tính lần lượt theo thứ tự tăng dần của $i$.

## Chứng minh tính đúng đắn

Mỗi đường tới $i$ có một trong hai vị trí áp chót nêu trên, do đó phí của nó ít nhất bằng vế phải. Ngược lại, nối một bước tới $i$ vào đường tối ưu đến vị trí áp chót cho giá trị nhỏ hơn sẽ đạt đúng vế phải. Hai giá trị đầu hiển nhiên đúng, nên theo quy nạp $D_N$ là đáp án.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$ khi chỉ giữ hai giá trị gần nhất. Dùng số nguyên 64 bit để lưu phí.
