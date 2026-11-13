## Thuật toán

Sinh đệ quy các số chỉ có chữ số $3,5,7$. Từ số $x$, thử nối từng chữ số vào bên phải. Chỉ tiếp tục nếu số mới không vượt $N$.

Dùng mặt nạ ba bit để ghi nhận các chữ số đã xuất hiện. Một số được cộng vào đáp án khi cả ba bit đều bằng $1$. Bắt đầu từ $x=0$ với mặt nạ rỗng, nhưng không đếm trạng thái ban đầu.

## Tính đúng đắn

Mỗi số chỉ dùng ba chữ số được sinh đúng một lần theo thứ tự chữ số của nó. Việc cắt nhánh không bỏ sót số hợp lệ vì nối thêm chữ số luôn làm số lớn hơn. Mặt nạ đầy đủ tương đương mỗi chữ số xuất hiện ít nhất một lần, nên thuật toán đếm chính xác các số 357 trong đoạn.

## Độ phức tạp

Với $d$ là số chữ số tối đa cần sinh, thời gian $O(3^d)$, bộ nhớ ngăn xếp $O(d)$. Với giới hạn bài, chỉ các số dài tối đa $9$ chữ số có thể được đếm. Dùng 64 bit khi nối chữ số.
