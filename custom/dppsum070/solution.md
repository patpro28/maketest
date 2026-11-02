Đặt $B_{i,j}=A_{i,j}$ để giữ nguyên giá trị của từng ô.

Tính tổng tiền tố hai chiều $P_{i,j}$ của bảng $B$ trên các hàng từ $1$ đến $i$ và các cột từ $1$ đến $j$. Khởi tạo hàng $0$ và cột $0$ bằng $0$. Công thức dựng bảng:

$P_{i,j}=B_{i,j}+P_{i-1,j}+P_{i,j-1}-P_{i-1,j-1}$.

Truy vấn có kết quả:

$P_{X_2,Y_2}-P_{X_1-1,Y_2}-P_{X_2,Y_1-1}+P_{X_1-1,Y_1-1}$.

Tính đúng đắn: từ hình chữ nhật tiền tố lớn, trừ phần phía trên và phần bên trái của vùng cần lấy. Góc trên trái đã bị trừ hai lần nên cộng lại một lần. Mỗi ô bên trong vùng còn đúng một lần, các ô bên ngoài bị loại hết. Vì bảng $B$ chứa đúng đóng góp cần tính của từng ô, công thức cho đúng kết quả truy vấn.

Thời gian $O(NM+Q)$, bộ nhớ $O(NM)$. Dùng số nguyên 64 bit cho các tổng vì trị tuyệt đối có thể đạt $500\cdot500\cdot10^9=2{,}5\cdot10^{14}$.
