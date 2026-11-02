Sàng Eratosthenes tới $10^6$. Đánh dấu $0,1$ không nguyên tố; lần lượt gạch các bội của mỗi số nguyên tố, bắt đầu từ bình phương của nó. Những số còn lại đúng là các số nguyên tố. Đặt $B_{i,j}=1$ nếu ô thỏa điều kiện, ngược lại đặt $B_{i,j}=0$.

Tính tổng tiền tố hai chiều $P_{i,j}$ của bảng $B$ trên các hàng từ $1$ đến $i$ và các cột từ $1$ đến $j$. Khởi tạo hàng $0$ và cột $0$ bằng $0$. Công thức dựng bảng:

$P_{i,j}=B_{i,j}+P_{i-1,j}+P_{i,j-1}-P_{i-1,j-1}$.

Truy vấn có kết quả:

$P_{X_2,Y_2}-P_{X_1-1,Y_2}-P_{X_2,Y_1-1}+P_{X_1-1,Y_1-1}$.

Tính đúng đắn: từ hình chữ nhật tiền tố lớn, trừ phần phía trên và phần bên trái của vùng cần lấy. Góc trên trái đã bị trừ hai lần nên cộng lại một lần. Mỗi ô bên trong vùng còn đúng một lần, các ô bên ngoài bị loại hết. Vì bảng $B$ chứa đúng đóng góp cần tính của từng ô, công thức cho đúng kết quả truy vấn.

Thời gian $O(L\log\log L+NM+Q)$ với $L=10^6$, bộ nhớ $O(L+NM)$. Số ô được đếm không vượt $NM\le250000$. Có thể dùng số nguyên 64 bit cho bảng tổng tiền tố để thống nhất cách cài đặt.
