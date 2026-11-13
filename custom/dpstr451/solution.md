Dùng chỉ số tiền tố $i$ và độ dài số cuối $d$. Gọi $F[i][d]$ là số cách chia tương ứng, và $P[i][d]=\sum_{t=1}^d F[i][t]$. Số mới bắt đầu tại vị trí $j=i-d$ nếu đánh số từ $0$. Bỏ trường hợp chữ số đầu là $0$. Nếu $j=0$, có một cách dùng đúng số mới. Nếu $j>0$, lấy tất cả số trước ngắn hơn $d$ qua $P[j][\min(j,d-1)]$. Số trước có cùng độ dài chỉ được tính nếu nó nhỏ hơn theo thứ tự từ điển, khi đó cộng $P[j][d]-P[j][d-1]$. Số dài hơn không thể nhỏ hơn.

Tính trước $LCP[u][v]$, độ dài tiền tố chung của hai hậu tố, từ phải sang trái. Hai chữ đầu khác nhau cho giá trị $0$, còn khi bằng nhau lấy $1+LCP[u+1][v+1]$. Khi so sánh hai mảnh dài $d$, dùng $LCP$ để tìm chữ khác nhau đầu tiên. Nếu cả $d$ chữ bằng nhau thì hai số bằng nhau và không được nối.

Mỗi cách chia chọn duy nhất độ dài số cuối. Với biểu diễn không có số $0$ đầu, phép so sánh theo độ dài rồi thứ tự từ điển đúng theo giá trị số. Vì vậy các chuyển đếm đúng các tiền tố có số cuối nhỏ hơn số mới.

Thời gian $O(N^2)$ và bộ nhớ $O(N^2)$. Dùng 16 bit cho bảng $LCP$ vì giá trị không vượt $4000$, và 32 bit cho bảng tổng đã lấy dư. Dùng mảng phẳng cho hai bảng để tránh chi phí cấp phát theo hàng.
