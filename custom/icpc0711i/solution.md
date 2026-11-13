## Chuyển hình học sang hai thứ tự

Với điểm $P=(x,y)$, đặt

$$\alpha(P)=\frac{x}{y},\qquad\beta(P)=\frac{x-X}{y}.$$

Một điểm kho báu $Q$ nằm trong tam giác có đáy $(0,0),(X,0)$ và đỉnh $P$ khi và chỉ khi

$$\alpha(Q)>\alpha(P),\qquad\beta(Q)<\beta(P).$$

Hai bất đẳng thức mô tả hai nửa mặt phẳng bên trong hai cạnh bên; cùng với $y_Q>0$ chúng xác định phần trong tam giác. Chúng cũng suy ra $X/y_Q>X/y_P$, tức $y_Q<y_P$. Dữ liệu không có điểm trên hàng rào nên không có trường hợp bằng nhau.

## Quét và Fenwick

Sắp xếp các điểm theo $\beta$ tăng dần để gán hạng. Sau đó quét theo $\alpha$ giảm dần. Với điểm hiện tại $P$, mọi điểm đã thêm vào cây đều có $\alpha$ lớn hơn. Truy vấn tổng trọng số ở các hạng $\beta$ nhỏ hơn hạng của $P$, lưu kết quả theo chỉ số ban đầu, rồi thêm trọng số của $P$.

So sánh các phân số bằng nhân chéo số nguyên. Dùng `__int128` cho tích để tránh sai số của số thực.

## Tính đúng đắn

Trước khi xử lý $P$, cây chứa chính xác các điểm thỏa bất đẳng thức thứ nhất. Truy vấn tiền tố lọc chính xác bất đẳng thức thứ hai. Do đó mỗi kho báu trong tam giác được cộng một lần và mọi điểm ngoài tam giác bị loại. Thêm $P$ sau truy vấn cũng loại kho báu dưới cọc.

## Độ phức tạp

$O(N\log N)$ thời gian, $O(N)$ bộ nhớ. Tổng trọng số cần số nguyên 64 bit.
