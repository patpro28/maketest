## Ý tưởng

Giữa vị trí $i-1$ và $i$ có một ranh giới đúng khi $D_i\ne0$. Bắt đầu đoạn đầu ở vị trí $1$. Mỗi khi gặp ranh giới, kết thúc đoạn hiện tại ở $i-1$ và mở đoạn mới tại $i$. Kết thúc đoạn cuối ở $N$. Lưu các đầu mút để in số đoạn trước.

## Chứng minh tính đúng đắn

Hai phần tử kề nhau ở vị trí $i-1,i$ bằng nhau đúng khi $D_i=0$. Do đó giữa các ranh giới liên tiếp, mọi phần tử bằng nhau. Tại mỗi ranh giới hai phần tử khác nhau, nên đoạn không thể mở rộng qua đó. Các đoạn thu được phủ toàn bộ dãy và chính là các đoạn tối đại.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Khi $N=1$, vẫn cần in đoạn $[1,1]$. Phần tử $D_1$ là giá trị đầu dãy nên không được dùng để tách đoạn.
