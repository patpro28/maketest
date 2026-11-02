### Ý tưởng

Dùng một dãy vị trí có sức chứa $N+Q$. Ban đầu người $i$ nằm ở vị trí $i$; các vị trí sau $N$ trống. Lưu vị trí hiện tại của mỗi người, mã người tại mỗi vị trí và biến $tail$ chỉ vị trí mới nhất đã dùng.

Segment tree trên các vị trí lưu $1$ nếu vị trí đang có người, ngược lại lưu $0$; nút trong lưu tổng. Khi chuyển người $x$ xuống cuối hàng, xóa dấu ở vị trí cũ, tăng $tail$ rồi đặt người $x$ và dấu $1$ vào vị trí $tail$.

Người thứ $k$ trong hàng nằm ở vị trí có dấu $1$ thứ $k$ từ trái sang phải. Đi xuống cây theo tổng con trái để tìm vị trí đó, rồi lấy mã người tương ứng.

### Chứng minh tính đúng đắn

Ban đầu, đọc các vị trí đang có người theo thứ tự tăng dần cho đúng hàng $1,2,\dots,N$. Giả sử tính chất này đúng trước một lần chuyển. Xóa vị trí của người $x$ giữ nguyên thứ tự mọi người khác. Vị trí mới lớn hơn tất cả vị trí đã dùng, nên thêm người $x$ ở đó đặt đúng người này xuống cuối. Vì vậy tính chất tiếp tục đúng, kể cả khi $x$ vốn đã ở cuối hàng.

Mỗi người có đúng một vị trí được đánh dấu, nên tổng tại một nút đếm đúng số người trong miền đó. Đi xuống theo thứ hạng tìm đúng vị trí có người thứ $k$, và bất biến trên bảo đảm đó chính là người thứ $k$ trong hàng.

### Độ phức tạp

Dựng cây mất $O(N+Q)$ thời gian; mỗi thao tác mất $O(\log(N+Q))$. Tổng thời gian $O(N+Q+Q\log(N+Q))$, bộ nhớ $O(N+Q)$.

### Lưu ý cài đặt

Có tối đa $Q$ lần chuyển, nên vị trí mới không vượt $N+Q$. Mã cũ còn lưu tại vị trí trống không ảnh hưởng vì cây không chọn vị trí đó.
