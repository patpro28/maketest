## Trạng thái và chuyển

Đặt $F[i][j]$ là số cách tạo tiền tố đích dài $j$ trong $i$ vị trí đầu của nguồn mà không chọn hai vị trí kề nhau. Biên $F[i][0]=1$, $F[0][j]=0$ với $j>0$.

Nếu bỏ $A_i$, có $F[i-1][j]$ cách. Nếu chọn $A_i=B_j$, vị trí $i-1$ bắt buộc không được chọn; phần trước phải nằm trong tiền tố dài $\max(0,i-2)$:

$$F[i][j]=F[i-1][j]+[A_i=B_j]F[\max(0,i-2)][j-1].$$

Đáp án là $F[N][M]$ modulo $10^9+7$.

## Tính đúng đắn

Phân loại theo vị trí cuối có được chọn hay không. Khi chọn, cấm vị trí kề trước bảo đảm mọi bộ chỉ số được tạo ra hợp lệ. Ngược lại, mọi bộ hợp lệ dùng vị trí $i$ đều có phần trước nằm trong tiền tố đã nêu. Tương ứng một-một giữa bộ chỉ số trước và sau khi thêm $i$ chứng minh công thức; các biên tính đúng cả trường hợp chỉ chọn một ký tự.

## Độ phức tạp và cài đặt

Giữ ba hàng: hàng đang tính, hàng $i-1$ và hàng $i-2$. Khi $i=1$, dùng hàng biên $0$ làm hàng cũ hơn. Thời gian $O(NM)$, bộ nhớ $O(M)$, tối đa $25\cdot10^6$ cặp chỉ số. Không dùng hàng $i-1$ cho chuyển chọn, vì sẽ tính cả hai vị trí kề nhau.
