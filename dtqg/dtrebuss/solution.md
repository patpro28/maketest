## DP theo số nhớ của phép cộng

Xử lý các cột từ phải sang trái, từ hàng đơn vị lên hàng cao nhất. Gọi $L$ là độ dài lớn nhất trong ba xâu.

Đặt $can[p][c]$ cho biết có thể điền $p$ cột thấp nhất và có số nhớ $c\in\{0,1\}$ sang cột tiếp theo. Khởi tạo $can[0][0]=true$.

Ở cột $p$, thử chữ số $a,b$ cho hai số hạng. Chúng phải khớp chữ số đã biết hoặc thay được dấu `*`. Nếu một số không có cột này thì chữ số của nó bắt buộc bằng $0$; chữ số $0$ bổ sung này không được in ra. Nếu cột là chữ số đầu tiên thực sự của một số thì cấm $0$, kể cả số có độ dài $1$.

Với số nhớ $c$, đặt

$$v=a+b+c,\qquad z=v\bmod10,\qquad c'=\lfloor v/10\rfloor.$$

Chỉ chuyển sang $can[p+1][c']$ nếu $z$ phù hợp với xâu tổng ở cột đó. Lưu lại số nhớ trước và bộ chữ số $(a,b,z)$ cho mỗi trạng thái đạt được lần đầu.

## Truy vết

Phải có $can[L][0]=true$. Nếu không, in `No Solution`. Số nhớ cuối bằng $1$ không được chấp nhận vì không còn chữ số đầu vào để chứa nó.

Từ trạng thái $(L,0)$, lần ngược các trạng thái đã lưu, điền bộ chữ số vào những cột thực sự tồn tại trong ba xâu, rồi in ba xâu theo thứ tự ban đầu.

Không cần số nguyên lớn: chỉ cộng hai chữ số và số nhớ trong mỗi bước.

## Chứng minh đúng

Sau $p$ cột, số nhớ là toàn bộ thông tin các cột thấp hơn có thể ảnh hưởng đến cột tiếp theo. Mọi phép điền hợp lệ phải có một cặp chữ số $a,b$ được thuật toán thử; chữ số tổng và số nhớ mới được xác định duy nhất bởi phép cộng. Ngược lại, mọi chuyển được nhận giữ nguyên các chữ số đã biết, không tạo số $0$ ở đầu và thỏa đúng phép cộng tại cột đó.

Quy nạp theo số cột cho thấy các trạng thái đạt được chính xác mô tả mọi cách điền hợp lệ. Kết thúc với số nhớ $0$ tương đương phép cộng đúng trên toàn bộ ba xâu. Truy vết chọn một đường chuyển hợp lệ nên tạo một đáp án đúng.

## Độ phức tạp

Mỗi cột có hai số nhớ, mỗi số nhớ thử không quá $10^2$ cặp chữ số. Thời gian $O(200L)$, bộ nhớ $O(L)$ cho truy vết. Với $L\le100000$, có không quá $2\cdot10^7$ cặp chữ số được xét.
