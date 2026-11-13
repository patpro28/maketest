## Ý tưởng

Gọi $D_{i,j,s}$ là điểm cao nhất khi xét $i$ ký tự đầu của $A$, $j$ ký tự đầu của $B$ và dùng đúng phí $s$. Nếu một tiền tố rỗng, chỉ có trạng thái phí $0$ đạt được với điểm $0$.

Bỏ vị trí $i$ hoặc $j$ cho hai ứng viên $D_{i-1,j,s}$ và $D_{i,j-1,s}$. Khi $A_i=B_j$, có thể ghép hai vị trí này. Nếu $s\ge X_i+Y_j$ và $D_{i-1,j-1,s-X_i-Y_j}$ đạt được, ứng viên thứ ba là giá trị đó cộng $P_{A_i}$. Lấy lớn nhất trong các ứng viên đạt được.

## Chứng minh tính đúng đắn

Trong một phương án trên hai tiền tố, nếu dùng cả hai vị trí cuối thì chúng phải ghép với nhau vì thứ tự ghép tăng nghiêm ngặt ở cả hai xâu. Bỏ cặp đó cho một phương án trên hai tiền tố ngắn hơn với phí giảm đúng $X_i+Y_j$. Nếu phương án không dùng ít nhất một vị trí cuối thì thuộc một trong hai chuyển bỏ qua. Ngược lại, cả ba phép chuyển đều tạo phương án hợp lệ và giữ đúng tổng phí. Theo quy nạp trên $i+j$, trạng thái $D_{N,M,S}$ cho đúng kết quả.

## Độ phức tạp

Thời gian $O(NM(S+1))$, bộ nhớ phụ $O(M(S+1))$ khi chỉ giữ hai lớp theo $i$. Dùng số nguyên 64 bit cho tổng điểm.
