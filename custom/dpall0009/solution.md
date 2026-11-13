## Ý tưởng

Sau khi vào một hàng, đường đi có thể đứng tại cột vừa vào hoặc đi ngang một đoạn. Nếu đổi hướng ngang thì sẽ quay lại ô vừa đi qua. Do chỉ được đi xuống khi đổi hàng, đường đi cũng không thể quay lại hàng trước. Vì vậy, phần đường trong mỗi hàng là một đoạn đi theo đúng một hướng hoặc chỉ gồm một ô.

Gọi $D_j$ là tổng tốt nhất khi kết thúc phần đường ở hàng trước tại cột $j$. Khi xét hàng $i$, quét từ trái sang phải để tính $L_j$ và từ phải sang trái để tính $R_j$.
$$
L_j=A_{i,j}+\max(D_j,L_{j-1}),\qquad
R_j=A_{i,j}+\max(D_j,R_{j+1}).
$$
Bỏ ứng viên nằm ngoài bảng. Cả hai lượt dùng cùng các giá trị $D_j$ của hàng trước. Khi xong, cập nhật $D_j=\max(L_j,R_j)$ cho hàng hiện tại.

Trước hàng đầu, đặt $D_j=0$ ở mọi cột để biểu diễn quyền chọn vị trí xuất phát. Sau hàng cuối, lấy giá trị lớn nhất trong tất cả các cột.

## Chứng minh tính đúng đắn

Xét một đường đi kết thúc tại cột $j$ của hàng hiện tại. Nếu đường đi vào hàng ở chính cột $j$, phần trước có tổng tốt nhất $D_j$. Nếu nó vào ở cột nhỏ hơn $j$, bước cuối trong hàng đi sang phải và thuộc lượt quét tính $L$. Nếu nó vào ở cột lớn hơn $j$, bước cuối đi sang trái và thuộc lượt tính $R$. Do mỗi lượt chỉ nối tiếp theo một hướng, phép chuyển không đi lại ô nào của hàng này. Các hàng trước cũng tách biệt với hàng đang xét. Theo quy nạp qua các hàng, giá trị tốt nhất tại từng cột được tính đúng.

## Độ phức tạp

Thời gian $O(MN)$ và bộ nhớ $O(N)$ khi đọc từng hàng. Dùng số nguyên 64 bit cho tổng.
