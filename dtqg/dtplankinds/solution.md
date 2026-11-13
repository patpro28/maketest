## Tách hai trường hợp cho mỗi loại

Đặt $f_i[t][p][q]$ là số phương án dùng $i$ loại đầu tiên, sử dụng đúng $t$ loại với số lượng dương và tiêu thụ đúng $(p,q)$ nguyên liệu.

Đặt thêm $g_i[t][p][q]$ là số phương án như trên nhưng bắt buộc dùng loại $i$. Khi đó:

$$f_i[t][p][q]=f_{i-1}[t][p][q]+g_i[t][p][q].$$

Để tính $g_i$, xét số sản phẩm loại $i$:

- Nếu đúng một sản phẩm, bỏ nó đi còn một phương án thuộc $f_{i-1}[t-1][p-a_i][q-b_i]$.
- Nếu ít nhất hai sản phẩm, bỏ một sản phẩm vẫn còn dùng loại $i$, tạo một phương án thuộc $g_i[t][p-a_i][q-b_i]$.

Vì vậy:

$$g_i[t][p][q]=f_{i-1}[t-1][p-a_i][q-b_i]+g_i[t][p-a_i][q-b_i].$$

Số hạng ngoài miền bằng $0$; $g_i[0][p][q]=0$. Mọi phép cộng lấy modulo $10^9$.

## Thứ tự tính

Chỉ giữ bảng $f$ của lớp trước và một bảng $g$:

1. Với loại mới, xóa bảng $g$ về $0$.
2. Duyệt $t=1,\ldots,K$, $p=a_i,\ldots,A$, $q=b_i,\ldots,B$ theo chiều tăng để tính $g$.
3. Sau khi tính xong toàn bộ $g$, cộng $g$ vào $f$.

Không cập nhật $f$ giữa chừng khi vẫn đang tính $g$, vì công thức cần nguyên lớp $f_{i-1}$. Ban đầu chỉ có $f[0][0][0]=1$. Đáp án là $f[K][A][B]$ sau mọi loại.

## Chứng minh đúng

Phân hoạch theo không dùng hoặc có dùng loại $i$ là rời nhau. Trong nhóm có dùng, hai trường hợp số lượng bằng một và ít nhất hai cũng rời nhau. Các phép bỏ một sản phẩm nêu trên đều là song ánh, giữ đúng số loại được sử dụng ở từng nhóm. Vì vậy cả hai truy hồi đếm đúng, không bỏ sót hoặc trùng phương án.

Duyệt lượng nguyên liệu tăng cho phép đọc đúng các ô $g$ nhỏ hơn. Giữ nguyên $f$ tới cuối lượt bảo đảm chỉ tăng số loại khi bắt đầu dùng loại mới. Quy nạp theo $i$ cho kết quả cuối đúng yêu cầu.

## Độ phức tạp và trường hợp biên

Thời gian $O(m(K+1)(A+1)(B+1))$, bộ nhớ $O((K+1)(A+1)(B+1))$ với hai bảng.

Khi $K=0$, chỉ phương án toàn số $0$ được nhận. Vì mọi hệ số đều dương, phương án đó chỉ phù hợp khi $A=B=0$. Không tăng số loại mỗi lần thêm một sản phẩm.
