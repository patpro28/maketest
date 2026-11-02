Tách các chữ số; nhận phần tử ngay khi gặp chữ số $7$. Mỗi phần tử chỉ đóng góp $1$ vào bộ đếm, kể cả khi chứa nhiều chữ số $7$.

Tính hai mảng tổng tiền tố: $C_i$ đếm số phần tử thỏa điều kiện trong $i$ vị trí đầu, $S_i$ cộng giá trị của tất cả $i$ phần tử đầu. Khởi tạo $C_0=S_0=0$.

Duyệt đầu phải $R$ từ $K$ đến $N$. Đoạn hiện tại bắt đầu ở $L=R-K+1$. Nếu $C_R-C_{R-K}<T$, bỏ qua đoạn. Ngược lại tính tổng $S_R-S_{R-K}$ và so sánh với kết quả tốt nhất trong các đoạn đã chấp nhận. Dùng một biến đánh dấu đã tìm thấy đoạn hợp lệ; đoạn hợp lệ đầu tiên luôn được nhận, kể cả khi tổng âm. Chỉ cập nhật vị trí khi tổng lớn hơn, giữ nguyên khi bằng nhau.

Tính đúng đắn: hiệu hai tiền tố đếm đúng số phần tử phù hợp và tính đúng tổng toàn bộ đoạn. Vì vậy bước lọc giữ đúng các đoạn có ít nhất $T$ phần tử phù hợp. Mỗi đoạn dài đúng $K$ được xét đúng một lần theo thứ tự đầu trái tăng dần. So sánh tổng của các đoạn được chấp nhận giữ đúng tổng lớn nhất; không cập nhật khi tổng bằng nhau giữ đúng vị trí sớm nhất. Nếu không có đoạn nào qua bước lọc, biến đánh dấu vẫn sai và kết quả là `NONE`.

Thời gian $O(N\log A_{\max})$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit cho tổng vì trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$. Không dùng tổng $-1$ làm dấu hiệu không có đáp án, vì đó có thể là tổng hợp lệ.
