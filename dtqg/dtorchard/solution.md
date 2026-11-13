## Đổi chi phí thành tổng hình chữ nhật

Gọi $T$ là tổng số cây chuối trong vườn. Một hình chữ nhật có $b$ cây chuối và $a$ cây táo sẽ tốn $T-b+a$ đơn vị tiền. Gán trọng số $+1$ cho cây chuối và $-1$ cho cây táo. Khi đó $b-a$ là tổng trọng số của hình chữ nhật, nên chỉ cần tìm tổng lớn nhất trong các hình chữ nhật hợp lệ rồi lấy $T$ trừ đi tổng đó.

## Cố định hai hàng biên

Có thể chuyển vị bảng để số hàng là cạnh ngắn hơn. Cố định hàng trên rồi lần lượt mở rộng hàng dưới. Khi thêm một hàng, cộng trọng số của hàng đó vào mảng tổng theo cột. Với hai hàng biên cố định, mỗi đoạn cột liên tiếp tương ứng với một hình chữ nhật và tổng của đoạn chính là trọng số hình chữ nhật.

Dùng Kadane để tìm tổng lớn nhất của đoạn cột không rỗng. Tổng tốt nhất của đoạn kết thúc ở cột hiện tại bằng trọng số cột cộng với phần dương của tổng tốt nhất kết thúc ở cột ngay trước. Khi cặp hàng đã phủ toàn bộ chiều cao, dải cột phải bỏ ít nhất một trong hai cột ngoài cùng để Bin còn đất. Xét riêng hai dải cột bỏ cột đầu hoặc bỏ cột cuối là đủ.

Mọi hình chữ nhật hợp lệ xuất hiện tại cặp hàng biên của nó và được phép trong ít nhất một lượt xét đoạn cột. Vì Kadane tìm đoạn tốt nhất trong mỗi lượt, tổng lớn nhất tìm được chính là tổng cần tối ưu.

## Độ phức tạp

Đặt $s=\min(N,M)$ và $t=\max(N,M)$. Có $O(s^2)$ cặp hàng biên, mỗi cặp xử lý trong $O(t)$. Tổng thời gian là $O(s^2t)$, bộ nhớ là $O(NM)$ để lưu bảng và $O(t)$ cho mảng tổng theo cột.
