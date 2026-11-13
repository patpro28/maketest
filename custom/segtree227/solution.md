## Đưa đường chuẩn về một mốc cố định

Đặt $B_i=A_i-id$. Với truy vấn trên đoạn $[L,R]$, đặt $Z=H-Ld$. Ta có

$$|A_i-H-(i-L)d|=|B_i-Z|.$$

Điều kiện $P\le H\le Q$ trở thành $P-Ld\le Z\le Q-Ld$. Mỗi lần cộng $x$ lên đoạn trong dãy $A$ cũng cộng đúng $x$ lên đoạn tương ứng của dãy $B$.

## Chọn mốc từ hai cực trị

Gọi $a=\min_{L\le i\le R}B_i$ và $b=\max_{L\le i\le R}B_i$. Với một mốc $Z$, sai số lớn nhất là

$$F(Z)=\max(b-Z,Z-a).$$

Mọi $B_i$ nằm giữa $a$ và $b$, và cả hai đầu mút đều xuất hiện. Vì thế hai cực trị đủ để tính $F(Z)$.

Hàm $F$ giảm khi $Z$ tiến tới $(a+b)/2$ từ bên trái và tăng khi $Z$ đi sang bên phải. Trên các số nguyên trong khoảng cho phép, chỉ cần thử hai ứng viên quanh trung điểm, sau khi chặn từng ứng viên vào khoảng $[P-Ld,Q-Ld]$. Có thể tính ứng viên thứ nhất bằng $a+\lfloor(b-a)/2\rfloor$, rồi lấy ứng viên thứ hai lớn hơn $1$. Cách này tính đúng phần nguyên dưới ngay cả khi hai cực trị âm. Tính $F$ tại hai mốc sau khi chặn và in giá trị nhỏ hơn.

## Cây đoạn có cập nhật lười

Dựng cây trên dãy $B$. Mỗi nút lưu min, max và nhãn cộng chờ. Phép ghép lấy min của hai giá trị nhỏ nhất và max của hai giá trị lớn nhất. Khi cộng $x$ phủ kín một nút, cộng $x$ vào cả hai cực trị và nhãn. Trước khi đi xuống các nút con, truyền nhãn để cực trị ở các đoạn nhỏ phản ánh đủ cập nhật.

Do cây duy trì đúng min và max của dãy $B$ hiện tại, cách chọn mốc ở trên tối ưu cho từng truy vấn của dãy $A$.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác tốn $O(\log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Tính tích $id$, nhãn lười, cực trị và mốc đã biến đổi bằng số nguyên 64 bit.
