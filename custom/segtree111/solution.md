# SEGTREE111 — Lời giải

### Ý tưởng

Đặt $b_i=[a_i>a_{i+1}]$ với $i<N$, và $b_N=0$. Lưu tổng $b_i$ trên cây. Khi gán $a_i$, chỉ tính lại $b_{i-1}$ và $b_i$ nếu tồn tại. Với truy vấn, tìm lá có giá trị $1$ đầu tiên trong $[l,r-1]$: bỏ qua nút ngoài đoạn hoặc có tổng bằng $0$, ưu tiên con trái.

### Chứng minh tính đúng đắn

Mỗi vị trí cần tìm tương ứng chính xác với một lá có $b_i=1$ trong đoạn tìm kiếm. Hai dấu hiệu được cập nhật là tất cả các cặp kề nhau chứa phần tử thay đổi. Các nút bị bỏ qua không chứa đáp án; duyệt con trái trước bảo đảm vị trí nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
