# STRINGA2 — Hướng dẫn giải

## Tách các đoạn số

Duyệt xâu từ trái sang phải. Khi gặp một chữ số, bắt đầu hoặc tiếp tục đoạn số hiện tại. Khi gặp chữ cái hoặc hết xâu, kết thúc đoạn. Chỉ kiểm tra cả đoạn số tối đại, không xét các đoạn con nằm bên trong.

Độ dài phải tính trên xâu ban đầu, bao gồm các chữ số $0$ ở đầu. Ví dụ, `0007` có giá trị $7$ nhưng độ dài bằng $4$.

## Theo từng subtask

- Subtask 1 (50%): $K=1$ nên mọi đoạn số đều hợp lệ. Chỉ cần tìm độ dài lớn nhất của các đoạn số.
- Subtask 2 (30%): giá trị mỗi đoạn số không vượt quá $10^{12}$, nên có thể chuyển đoạn thành số nguyên 64 bit và kiểm tra chia hết bằng phép lấy dư. Giới hạn này là giới hạn giá trị, không phải độ dài; đoạn vẫn có thể chứa rất nhiều chữ số $0$ ở đầu.
- Subtask 3 (20%): đoạn số có thể dài đến $10^5$ chữ số, nên dùng một trong hai cách dưới đây.

## Cách 1: Tính số dư khi đọc chữ số

Với mỗi đoạn số, khởi tạo $r=0$. Mỗi khi đọc thêm chữ số $d$, cập nhật:

$$r=(10r+d)\bmod K.$$

Nếu giá trị phần đã đọc là $v$ thì khi thêm $d$, giá trị mới là $10v+d$. Do đó công thức luôn duy trì đúng số dư của phần đã đọc khi chia cho $K$, mà không cần lưu cả số nguyên lớn.

Khi kết thúc đoạn, nếu $r=0$ thì dùng độ dài đoạn để cập nhật đáp án lớn nhất. Cần xử lý cả đoạn nằm ở cuối xâu. Nếu không có đoạn hợp lệ, in $0$.

Lời giải tham khảo: `sol/correct.cpp`.

## Cách 2: Vận dụng dấu hiệu chia hết

Có thể tách từng đoạn bằng các hàm `find_first_of`, `find_first_not_of` và `substr`, rồi áp dụng dấu hiệu tương ứng:

| $K$ | Điều kiện chia hết |
| --- | --- |
| $1$ | Mọi số nguyên không âm đều thỏa mãn |
| $2$ | Chữ số cuối là số chẵn |
| $3$ | Tổng chữ số chia hết cho $3$ |
| $4$ | Số tạo bởi hai chữ số cuối chia hết cho $4$ |
| $5$ | Chữ số cuối là $0$ hoặc $5$ |
| $6$ | Đồng thời chia hết cho $2$ và $3$ |
| $7$ | Chia số thành các nhóm ba chữ số từ phải sang trái; tổng luân phiên cộng, trừ các nhóm chia hết cho $7$ |
| $8$ | Số tạo bởi ba chữ số cuối chia hết cho $8$ |
| $9$ | Tổng chữ số chia hết cho $9$ |

Nếu đoạn có ít hơn hai hoặc ba chữ số, dùng toàn bộ đoạn khi kiểm tra dấu hiệu cho $4$ hoặc $8$.

Dấu hiệu cho $7$ đúng vì $1000\equiv-1\pmod7$. Ví dụ, với `1234567`, các nhóm từ phải sang trái là $567,234,1$; tính $567-234+1=334$. Vì $334$ không chia hết cho $7$, số ban đầu cũng không chia hết cho $7$. Tổng luân phiên có thể âm; chỉ cần kiểm tra số dư có bằng $0$ hay không.

Lời giải tham khảo: `sol/divisibility_rules.cpp`.

## Độ đúng và độ phức tạp

Mỗi đoạn số tối đại được xét đúng một lần. Phép kiểm tra xác định đúng việc chia hết cho $K$, nên việc lấy độ dài lớn nhất trong các đoạn hợp lệ cho đúng đáp án. Nếu không có đoạn hợp lệ, kết quả là $0$ theo yêu cầu.

Cả hai cách đều có thời gian $O(|S|)$. Cách tính số dư dùng $O(1)$ bộ nhớ phụ ngoài xâu đầu vào; cách cắt xâu dùng tối đa $O(|S|)$ bộ nhớ phụ.
