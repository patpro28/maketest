## Mặt hiện phụ thuộc vào vị trí cuối

Mỗi lần một quân bài di chuyển sang vị trí kề, nó bị lật. Vì vậy quân bài ban đầu ở vị trí $i$, cuối cùng ở vị trí $p$, hiện $A_i$ nếu $p-i$ chẵn và hiện $B_i$ nếu $p-i$ lẻ. Điều này không phụ thuộc vào đường đi của các thao tác.

Với một hoán vị cuối cùng cố định của các quân bài có nhãn, số đổi chỗ kề nhỏ nhất là số nghịch thế. Ta xây dựng hoán vị từ trái sang phải bằng quy hoạch động trên tập con.

## Trạng thái và chuyển tiếp

Đặt $dp[mask][v]$ là chi phí nhỏ nhất để xếp các quân bài trong $mask$ thành tiền tố không giảm, có giá trị cuối **không vượt quá** $v$, với $0\le v\le50$.

Khởi tạo tiền tố rỗng chi phí $0$. Với mỗi $mask$, lấy cực tiểu tiền tố theo $v$ để có đúng ý nghĩa trên. Vị trí kế tiếp (đánh số từ $0$) là $p=\operatorname{popcount}(mask)$.

Thử quân bài $i$ chưa chọn. Xác định giá trị hiện $x$ theo tính chẵn lẻ của $p-i$. Nếu $dp[mask][x]$ hữu hạn, có thể nối quân bài này. Chi phí thêm là số quân bài chưa chọn có chỉ số ban đầu nhỏ hơn $i$:

$$i-\operatorname{popcount}(mask\mathbin{\&}((1\ll i)-1)).$$

Cập nhật trạng thái mới tại giá trị cuối $x$. Kết quả là trạng thái toàn bộ quân bài, ngưỡng $50$.

## Tính đúng đắn

Mỗi hoán vị được xây dựng bởi duy nhất một chuỗi lựa chọn quân bài. Điều kiện giá trị cuối kiểm tra chính xác dãy hiện không giảm. Khi thêm quân bài $i$, những quân bài có chỉ số nhỏ hơn nhưng chưa chọn sẽ nằm sau nó trong hoán vị cuối: đây chính xác là các nghịch thế mới, mỗi nghịch thế được tính một lần.

Mọi hoán vị cuối có thể thực hiện với đúng số nghịch thế bằng đổi chỗ kề. Tính chẵn lẻ di chuyển bảo đảm mặt bài lúc đó đúng với trạng thái đã tính. Quy hoạch động lấy nhỏ nhất trên mọi hoán vị hợp lệ, nên cho số thao tác tối ưu. Theo điều kiện đầu vào, đáp án luôn tồn tại.

## Độ phức tạp

$O((N+51)2^N)$ thời gian và $O(51\cdot2^N)$ bộ nhớ. Số nghịch thế không vượt $18\cdot17/2=153$, nên có thể lưu chi phí bằng một byte, dùng $255$ làm vô cực.
