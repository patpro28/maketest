Đặt $F[i]$ là số đoạn ít nhất của tiền tố dài $i$, với $F[0]=0$. Từ điểm cắt $i$, quét về phải và đánh dấu các chữ đã gặp. Dừng khi gặp chữ lặp hoặc đã đạt cận $R$. Với mỗi đoạn dài ít nhất $L$, cập nhật tiền tố ở đầu phải bằng $F[i]+1$.

Một đoạn chứa chữ lặp vẫn chứa chữ lặp khi mở rộng, nên dừng tại lần lặp đầu tiên không bỏ sót mảnh hợp lệ. Các chuyển còn lại liệt kê đúng mọi mảnh có thể đứng sau điểm cắt. Quy nạp theo độ dài tiền tố cho thấy giá trị nhỏ nhất được tính đúng.

Có nhiều nhất $26$ chữ khác nhau trong một mảnh. Thời gian $O(26N)$ và bộ nhớ $O(N)$.
