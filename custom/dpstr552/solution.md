Gọi $F[i][j]$ là cặp (chi phí, đầu trái) tốt nhất để biến tiền tố $A[1..i]$ thành một đoạn không rỗng của $B$ kết thúc ở $j$. So sánh hai cặp theo chi phí trước, rồi đầu trái. Với $i=0$ và $j>0$, chọn đoạn một chữ $B_j$ với chi phí $1$. Cột $j=0$ không hợp lệ.

Với $i,j>0$, có thể xóa $A_i$ từ $F[i-1][j]$, chèn $B_j$ từ $F[i][j-1]$ hoặc ghép hai chữ cuối từ $F[i-1][j-1]$. Ba chuyển này giữ nguyên đầu trái. Ngoài ra có thể bắt đầu đoạn ngay ở $j$ bằng cách xóa $i-1$ chữ rồi ghép $A_i$ với $B_j$. Trường hợp xóa hết rồi chèn một chữ đã được xét bằng chuyển xóa từ hàng $i=0$.

Mọi phương án được phân loại theo bước cuối, với mảnh một chữ mới bắt đầu được xét riêng khi bước đó ghép ký tự. Một cặp có chi phí lớn hơn, hoặc có cùng chi phí nhưng đầu trái lớn hơn, không tốt hơn sau bất kỳ phần mở rộng nào. Do đó mỗi ô chỉ cần giữ cặp tốt nhất. Cuối cùng lấy nhỏ nhất theo bộ ba (chi phí, đầu trái, đầu phải) trên hàng $N$.

Thời gian $O(NM)$, bộ nhớ $O(M)$ với một hàng và biến giữ ô chéo.
