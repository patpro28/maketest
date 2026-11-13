## Ý tưởng và trạng thái

Tính $P[L][R]$ theo công thức đoạn đối xứng: hai đầu bằng nhau và đoạn trong đối xứng, với đoạn dài $1,2$ được xử lý trực tiếp. Mỗi ô đúng tạo một ứng viên $(R-L+1,L)$. Chọn ứng viên có độ dài lớn nhất, rồi vị trí bắt đầu nhỏ nhất.

## Tính đúng đắn

Điều kiện hai đầu và đoạn trong là cần và đủ cho đối xứng, nên quy nạp theo độ dài cho bảng đúng. Mọi đoạn đều được xét đúng một lần theo hai đầu mút. So sánh độ dài và vị trí bắt đầu theo đúng thứ tự yêu cầu cho kết quả tối ưu và xử lý đúng trường hợp hòa.

## Nén bộ nhớ

Duyệt $L$ giảm dần, $R$ tăng dần. Trước khi ghi $f[R]=P[L][R]$, giá trị cũ tại đó là $P[L+1][R]$. Biến tạm giữ giá trị cũ của ô trước, tức $P[L+1][R-1]$, để tính đoạn trong. Không dùng $f[R-1]$ sau cập nhật vì nó thuộc hàng hiện tại.

Thời gian $O(N^2)$, bộ nhớ phụ $O(N)$. Số ô chính không quá $N(N+1)/2=12502500$.
