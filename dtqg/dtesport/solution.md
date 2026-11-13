## Thông tin trên cây đoạn

Mỗi nút lưu số phần tử, giá trị ở hai đầu, công sai của cặp đầu và cặp cuối nếu có, cùng độ dài tiền tố, hậu tố và đoạn con cấp số cộng dài nhất.

Khi ghép đoạn trái $A$ với đoạn phải $B$, công sai tại ranh giới là $k=B_{\mathrm{đầu}}-A_{\mathrm{cuối}}$. Một cấp số cộng đi qua ranh giới phải dùng công sai này.

- Phần bên trái dài bằng hậu tố cấp số cộng của $A$ nếu công sai của cặp cuối bằng $k$. Nếu công sai khác hoặc $A$ chỉ có một phần tử, lấy đúng phần tử cuối.
- Phần bên phải được tính tương tự bằng tiền tố cấp số cộng của $B$ và công sai của cặp đầu.

Gọi $a,b$ là hai độ dài vừa tìm. Đoạn tốt nhất đi qua ranh giới dài $a+b$. So sánh nó với đáp án nằm trọn trong từng con. Tiền tố được nối sang $B$ nếu $a$ phủ hết $A$. Hậu tố được nối sang $A$ nếu $b$ phủ hết $B$. Công sai của cặp đầu được lấy từ $A$ khi $A$ có ít nhất hai phần tử, và bằng $k$ khi $A$ chỉ có một phần tử. Công sai của cặp cuối được xử lý đối xứng.

## Cập nhật lười

Viết biểu thức cập nhật dưới dạng $f(i)=u+vi$ với $u=S-LC$ và $v=C$ khi dùng cùng cách đánh chỉ số cho $L$ và $i$. Trên một nút được phủ hoàn toàn, ta xử lý theo loại cập nhật.

- Khi cộng $f(i)$, các hiệu liên tiếp đều tăng thêm $v$. Vì quan hệ bằng nhau giữa các hiệu được giữ nguyên, ba độ dài đã lưu giữ nguyên. Cập nhật hai giá trị đầu mút bằng $f$ tại vị trí tương ứng và cộng $v$ vào hai công sai.
- Khi gán $f(i)$, cả đoạn là một cấp số cộng có công sai $v$. Cả ba độ dài bằng kích thước nút. Hai giá trị đầu mút là giá trị của $f$ tại vị trí tương ứng.

Thẻ lười lưu loại thao tác và hai hệ số của $f$. Phép gán mới thay thế thẻ cũ. Phép cộng mới cộng từng hệ số vào thẻ cũ và giữ loại thao tác đã lưu. Khi chỉ xử lý một phần nút, đẩy thẻ xuống hai con trước rồi ghép kết quả theo thứ tự từ trái sang phải.

## Tính đúng đắn

Ở lá, đoạn có một phần tử nên cả ba độ dài bằng $1$. Khi ghép hai đoạn, mỗi cấp số cộng hoặc nằm trọn trong một con hoặc qua ranh giới. Với loại qua ranh giới, công sai $k$ là bắt buộc, và phép ghép lấy đúng hậu tố và tiền tố dài nhất tương thích với $k$. Vì vậy thông tin của nút cha chính xác nếu hai con chính xác. Các phép cập nhật phủ trọn nút bảo toàn ý nghĩa của mọi trường như trên, còn cập nhật một phần đẩy đúng phép biến đổi xuống các con. Do đó mọi truy vấn nhận được thông tin chính xác của đoạn yêu cầu.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác tốn $O(\log N)$ và cây dùng $O(N)$ bộ nhớ. Dùng số nguyên 64 bit cho giá trị, công sai và các hệ số cập nhật vì nhiều phép cộng có thể tích lũy trên cùng một đoạn.
