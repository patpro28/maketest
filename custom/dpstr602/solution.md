## Trạng thái và chuyển

Đặt $P[L][R]$ là tính đối xứng của đoạn liên tiếp. Đoạn một ký tự luôn đúng; đoạn dài $2$ đúng khi hai chữ bằng nhau; đoạn dài hơn đúng khi hai đầu bằng nhau và $P[L+1][R-1]$ đúng.

Cộng $1$ vào đáp án cho mỗi ô đúng. Không cộng độ dài đoạn và không gộp các đoạn cùng nội dung.

## Tính đúng đắn

Điều kiện trên là cần và đủ vì bỏ hai đầu bằng nhau của một xâu đối xứng sẽ còn xâu đối xứng, và thêm cùng một chữ ở hai đầu xâu đối xứng vẫn đối xứng. Theo quy nạp, mỗi ô nhận đúng giá trị. Mỗi cặp $(L,R)$ chỉ được duyệt một lần, nên tổng số ô đúng chính là số đoạn cần đếm.

## Độ phức tạp và cài đặt

Duyệt đầu trái giảm, đầu phải tăng; nén một hàng với biến tạm lưu ô chéo của hàng trước. Thời gian $O(N^2)$, bộ nhớ $O(N)$. Đáp án không quá $N(N+1)/2=12502500$; có thể dùng 64 bit cho biến tổng. Đoạn rỗng chỉ dùng làm biên, không cộng vào kết quả.
