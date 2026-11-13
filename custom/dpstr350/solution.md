## Trạng thái và chuyển

Đặt $F[i][j][t][s]$ là số cách tạo tiền tố đích dài $j$ trong $i$ vị trí đầu của nguồn, có đúng $t$ nhóm, với $s=1$ nếu vị trí $i$ được chọn và $s=0$ nếu không. Khởi tạo $F[0][0][0][0]=1$; các trạng thái khác bằng $0$.

Bỏ vị trí hiện tại luôn làm trạng thái cuối bằng $0$:

$$F[i][j][t][0]=F[i-1][j][t][0]+F[i-1][j][t][1].$$

Chỉ được chọn nếu $j>0$ và $A_i=B_j$. Khi đó:

$$F[i][j][t][1]=F[i-1][j-1][t][1]+[t>0]F[i-1][j-1][t-1][0].$$

Số hạng đầu nối tiếp nhóm đang có; số hạng sau mở nhóm mới. Khi chữ không khớp, trạng thái kết thúc bằng chọn bằng $0$. Lấy tổng hai trạng thái cuối ở $(N,M,K)$ modulo $10^9+7$.

## Tính đúng đắn

Nếu vị trí hiện tại không chọn, các nhóm trước đó không đổi. Nếu chọn, nó thuộc cùng nhóm với vị trí trước khi vị trí trước cũng được chọn; nếu vị trí trước không chọn, nó bắt đầu duy nhất một nhóm mới. Đây là các trường hợp rời nhau và bao phủ mọi cách chọn. Vì thế chuyển bảo toàn cả nội dung đích lẫn số nhóm chính xác, và theo quy nạp đếm mỗi bộ chỉ số một lần.

## Độ phức tạp và cài đặt

Nén theo $i$, dùng hai lớp mảng để chuyển trạng thái. Không được khởi tạo trạng thái rỗng có nhóm hay có vị trí cuối được chọn. Với $K=0$, $M\ge1$, đáp án bằng $0$. Thời gian $O(NM(K+1))$, bộ nhớ $O(M(K+1))$; tính cả hai trạng thái cuối có tối đa $2\cdot2000^2\cdot6=48\cdot10^6$ ô chính.
