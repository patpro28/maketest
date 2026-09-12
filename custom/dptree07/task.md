### Đề bài

Trên một **nông trại**, Farmer John có $N$ **chuồng** được đánh số từ $1$ đến $N$. Các chuồng được nối với nhau bằng những con đường nội bộ sao cho giữa hai chuồng bất kỳ **chỉ tồn tại nhiều nhất một đường đi**.

Mỗi chuồng cần được sơn một trong **3 màu khác nhau**. Hiện tại đã có $K$ chuồng được sơn sẵn, các chuồng còn lại thì chưa.

Bò Bessie rất dễ bị rối trí nếu **hai chuồng được nối trực tiếp với nhau** lại có **cùng màu sơn**, vì vậy Farmer John muốn đảm bảo rằng điều này **không bao giờ xảy ra**.

Hãy xác định **số cách khác nhau** để sơn các chuồng chưa được sơn sao cho:

- Tất cả $N$ chuồng đều được sơn,
- Không có hai chuồng kề nhau nào có cùng màu.

Kết quả cần được tính **theo modulo** $(10^9 + 7)$.

### Dữ liệu vào

- Dòng đầu gồm hai số nguyên $N$ và $K$ — số lượng chuồng và số chuồng đã được sơn.
- $N-1$ dòng tiếp theo, mỗi dòng gồm hai số nguyên $x, y$ mô tả một con đường nối trực tiếp giữa chuồng $x$ và chuồng $y$.
- $K$ dòng cuối, mỗi dòng gồm hai số nguyên $b, c$ cho biết chuồng $b$ đã được sơn màu $c$.

### Dữ liệu ra

- In ra **một số nguyên duy nhất** là số cách hợp lệ để sơn các chuồng còn lại, lấy modulo $(10^9 + 7)$.

### Ràng buộc

- $1 \le N \le 10^5$
- $0 \le K \le N$
- $1 \le x, y \le N,\; x \ne y$
- $1 \le b \le N$
- $1 \le c \le 3$
- Hệ thống chuồng **không chứa chu trình**

### Sample Input 1
    4 1
    1 2
    1 3
    1 4
    4 3

### Sample Output 1
    8

### Giải thích

Nông trại có $4$ chuồng được nối theo dạng cây, trong đó chuồng số $4$ đã được sơn sẵn màu $3$.
Các chuồng còn lại được sơn sao cho không có hai chuồng nối trực tiếp nào cùng màu.
Tổng cộng có $8$ cách sơn hợp lệ thỏa mãn các điều kiện trên.
