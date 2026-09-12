### Đề bài

Công ty X có một mạng gồm $N$ máy tính. Có $N-1$ đường nối, mỗi đường nối kết nối một cặp máy tính và có độ trễ nhất định. Đảm bảo rằng toàn bộ hệ thống luôn liên thông.

Các kỹ sư của X cho rằng mạng hiện tại hơi chậm và muốn cải thiện nó. Họ thực hiện $Q$ thí nghiệm.

Với mỗi truy vấn, bạn được cung cấp một liên kết trực tiếp mới giữa hai máy tính $u, v$ với độ trễ $w$. Khi thêm liên kết mới này và loại bỏ đúng một liên kết cũ trong mạng, hãy kiểm tra xem mạng mới có **tốt hơn** mạng cũ hay không.

Một mạng mới được coi là **tốt hơn** nếu:

- Tổng độ trễ của toàn bộ mạng **giảm nghiêm ngặt**.
- Mạng vẫn **liên thông**.

Lưu ý: Các truy vấn độc lập; sau mỗi truy vấn, mạng trở về trạng thái ban đầu.

### Dữ liệu vào

- Dòng 1: số nguyên $N$ — số lượng máy tính.
- $N-1$ dòng tiếp theo: mỗi dòng chứa $u, v, w$ — đường nối giữa $u$ và $v$ có độ trễ $w$.
- Dòng tiếp theo chứa số nguyên $Q$.
- $Q$ dòng tiếp theo: mỗi dòng chứa $u, v, w$ — liên kết mới đề xuất.

### Dữ liệu ra

Với mỗi truy vấn, in ra:

- `YES` nếu có thể thay thế đúng một đường cũ bằng đường mới để cải thiện mạng.
- `NO` nếu không thể.

### Ràng buộc

- $1 \le N, Q \le 3\times 10^5$.
- $1 \le w \le 10^9$

### Sample Input
    5
    1 2 2
    1 3 3
    3 4 5
    3 5 4
    2
    1 4 4
    4 5 6

### Sample Output
    YES
    NO

### Giải thích

- Truy vấn 1: Ta loại bỏ đường $3\to 4$ và thêm đường $1\to 4$, độ lag giảm 1.
- Truy vấn 2: Việc thêm đường vào sẽ tăng độ lag.