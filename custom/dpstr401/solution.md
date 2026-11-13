Gọi $F[i]$ là số cách chia tiền tố dài $i$. Đặt $F[0]=1$. Cộng $F[i-1]$ khi ký tự cuối từ `1` đến `9`. Nếu hai ký tự cuối biểu diễn một số từ $10$ đến $26$ thì cộng thêm $F[i-2]$. Lấy dư sau mỗi lần cộng.

Hai nhóm cách chia dùng độ dài mảnh cuối khác nhau nên rời nhau. Trong mỗi nhóm, bỏ mảnh cuối cho tương ứng một-một với các cách chia tiền tố còn lại. Duyệt theo thứ tự tăng của $i$ cho kết quả đúng.

Thời gian $O(N)$ và bộ nhớ $O(N)$. Có thể giữ hai giá trị cũ để dùng $O(1)$ bộ nhớ.
