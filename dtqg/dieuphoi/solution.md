# Lời giải DIEUPHOI — Sắp đội hình trên đường thẳng

## Bỏ chiều dài và khoảng cách an toàn khỏi điều kiện

Đặt $P_1=0$ và $P_i=\sum_{j<i}(L_j+G_j)$. Gọi $Y_i=X_i-P_i$, $B_i=A_i-P_i$. Khi đó:

$$X_{i+1}\ge X_i+L_i+G_i\iff Y_{i+1}\ge Y_i,$$

và $|X_i-A_i|=|Y_i-B_i|$. Bài toán trở thành hiệu chỉnh dãy $B$ thành dãy không giảm với tổng sai lệch tuyệt đối nhỏ nhất. Không được sắp xếp lại $B$, vì thứ tự xe cố định.

## Quy hoạch động làm cơ sở

Gọi $F_i(x)$ là chi phí nhỏ nhất của $i$ phần tử đầu, với $Y_i=x$:

$$F_i(x)=|x-B_i|+\min_{y\le x}F_{i-1}(y).$$

Một nghiệm tối ưu có thể chọn các mức $Y_i$ trong tập các $B_j$: mỗi khối cùng mức có thể đưa về một trung vị của các mục tiêu trong khối. Vì vậy với $N$ nhỏ có thể nén các $B_j$ và tính DP bằng min tiền tố trong $O(N^2)$ thời gian, $O(N)$ bộ nhớ.

## Slope trick với một max-heap

Đặt $H_i(x)=\min_{y\le x}F_i(y)$. Đây là hàm lồi, không tăng, có thể biểu diễn

$$H_i(x)=M_i+\sum_{p\in Q_i}\max(p-x,0).$$

Các điểm gãy $p$ được lưu trong max-heap; $M_i$ là giá trị nhỏ nhất của hàm và cũng là chi phí tối ưu của tiền tố.

Khi thêm mục tiêu $b=B_i$:

1. Đưa $b$ vào heap.
2. Nếu điểm lớn nhất $p$ trong heap lớn hơn $b$, tăng $M$ thêm $p-b$, bỏ một bản sao của $p$, rồi đưa thêm một bản sao của $b$ vào heap.
3. Nếu không có $p>b$, không thay đổi $M$.

Đây là kết quả của việc cộng $|x-b|$ rồi lấy min tiền tố: phần độ dốc dương ở bên phải bị loại, còn nếu $b$ nằm bên trái điểm gãy lớn nhất thì một đơn vị điểm gãy đó chuyển về $b$ và giá trị nhỏ nhất tăng $p-b$. Mỗi bước tăng kích thước heap đúng một phần tử.

## Chứng minh đúng

Phép đổi biến tương đương cả điều kiện và chi phí. Công thức DP xét mọi giá trị hợp lệ cho phần tử trước, nên đúng. Ban đầu hàm chi phí bằng $0$, ứng với heap rỗng và $M=0$. Quy tắc cập nhật heap biểu diễn đúng phép biến đổi $H_i(x)=\min_{y\le x}(H_{i-1}(y)+|y-B_i|)$, nên bất biến được giữ sau mỗi phần tử. Khi $x$ đủ lớn, mọi số hạng trong biểu diễn bằng $0$; vì thế giá trị nhỏ nhất là $M_i$. Kết thúc trả $M_N$ cho đáp án yêu cầu.

## Độ phức tạp và giới hạn số

- Thời gian $O(N\log N)$, bộ nhớ $O(N)$.
- Dùng `long long` cho tổng $P_i$, các mục tiêu đã đổi biến và đáp án. $P_i$ có thể gần $4\cdot10^{11}$ dù tọa độ đầu vào chỉ tới $10^9$.
- Chọn mọi $Y_i=0$ cho một phương án hợp lệ; chi phí không vượt $N(10^9+2\cdot10^6(N-1))<8.1\cdot10^{16}$, nằm trong số nguyên có dấu 64 bit.
- Với $N=1$ không có dòng khoảng cách; đáp án bằng $0$.

## Kiểm chứng độc lập

Oracle dùng PAVA: tạo các khối liên tiếp, giữ trung vị và gộp hai khối nếu các trung vị vi phạm thứ tự. Các heap trong oracle giữ giá trị của khối và tính trực tiếp tổng sai lệch, không dùng truy hồi cập nhật một heap của lời giải mẫu. Với $N\le3000$, oracle còn đối chiếu PAVA với DP nén tọa độ $O(N^2)$.
