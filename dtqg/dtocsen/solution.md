## Mô hình một ngày

Đặt $S_k=\sum_{i=0}^{k-1}P_i$ là tổng độ dịch chuyển của $k$ bước đầu, với $S_0=0$. Gọi $B_k$ là độ cao sau $k$ bước nếu bắt đầu ngày ở độ cao $0$ và mô phỏng đủ cả ngày.

Nếu bắt đầu ở độ cao $h\ge0$, độ cao sau $k$ bước bằng
$\max(h+S_k,B_k)$. Công thức đúng khi $k=0$. Khi thêm một bước, mỗi thành phần tăng thêm $P_k$ rồi kết quả được chặn dưới bởi $0$. Vì $B_{k+1}=\max(0,B_k+P_k)$, công thức vẫn đúng.

## Tìm ngày đầu tiên thoát ra

Mô phỏng ngày $0$ và trả lời ngay nếu ốc sên đạt $H$. Nếu ngày $0$ thất bại, ta có $B_k<H$ với mọi $k$. Vì vậy, một ngày bắt đầu ở độ cao $h$ thoát được khi và chỉ khi $h+M\ge H$, với $M=\max_{0\le k\le N}S_k$. Việc tính cả $S_0$ an toàn vì khi chọn ngày sớm nhất, ốc sên chưa đạt $H$ ở cuối ngày trước đó.

Đặt $S=S_N$ và $b=B_N$. Ngày $1$ bắt đầu ở độ cao $b$. Từ công thức trên, một ngày bắt đầu ở độ cao $h$ sẽ kết thúc ở độ cao $\max(h+S,b)$. Nếu $S\le0$, độ cao đầu ngày luôn bằng $b$ từ ngày $1$ trở đi. Nếu $S>0$, độ cao đầu ngày $d\ge1$ là $b+(d-1)S$.

- Nếu $b+M\ge H$, chọn ngày $1$.
- Nếu $b+M<H$ và $S\le0$, in hai giá trị $-1$.
- Nếu $b+M<H$ và $S>0$, ngày đầu tiên thỏa điều kiện là $1+\left\lceil (H-M-b)/S\right\rceil$.

Mô phỏng các bước trong ngày đã chọn từ độ cao đầu ngày tương ứng. Bước đầu tiên đạt $H$ là bước cần tìm. Các ngày trước đó đã được loại bằng điều kiện $h+M\ge H$.

## Độ phức tạp

Thời gian $O(N)$ và bộ nhớ $O(N)$ để lưu dãy bước. Dùng số nguyên 64 bit cho độ cao, tổng tiền tố và chỉ số ngày.
