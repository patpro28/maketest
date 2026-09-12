### Đề bài

Trong một chương trình **giáo dục STEM**, một trường học xây dựng mô hình **cây tri thức** gồm $n$ điểm học tập, được nối với nhau theo dạng cây (không có chu trình).

Mỗi điểm học tập $v$ có một **khoảng điểm đánh giá cho phép**, từ $l_v$ đến $r_v$. Ban tổ chức muốn gán cho mỗi điểm học tập một **giá trị đánh giá** $a_v$ sao cho $l_v \le a_v \le r_v$.

Để khuyến khích sự đa dạng và chênh lệch hợp lý giữa các điểm học tập có liên kết trực tiếp, **mức độ nổi bật giáo dục** của toàn bộ cây được định nghĩa là tổng:

$$
\sum_{(u,v)} |a_u - a_v|
$$

với tổng được tính trên tất cả các cạnh $(u,v)$ của cây.

Hãy xác định **mức độ nổi bật giáo dục lớn nhất có thể đạt được**.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $t$ — số lượng bộ test.
- Với mỗi bộ test:
    - Dòng đầu chứa số nguyên $n$ — số lượng điểm học tập.
    - $n$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $l_i, r_i$.
    - $n-1$ dòng tiếp theo, mỗi dòng chứa hai số $u, v$ mô tả một liên kết giữa hai điểm học tập $u$ và $v$.

### Dữ liệu ra

- Với mỗi bộ test, in ra một số nguyên — mức độ nổi bật giáo dục lớn nhất của cây.

### Ràng buộc

- $1 \le t \le 250$
- $2 \le n \le 10^5$
- $1 \le l_i \le r_i \le 10^9$
- $1 \le u, v \le n,\ u \ne v$
- Tổng $n$ của tất cả bộ test không vượt quá $2 \cdot 10^5$
- Dữ liệu đảm bảo tạo thành một cây

### Sample Input 1
    3
    2
    1 6
    3 8
    1 2
    3
    1 3
    4 6
    7 9
    1 2
    2 3
    6
    3 14
    12 20
    12 19
    2 12
    10 17
    3 17
    3 2
    6 5
    1 5
    2 6
    4 6

### Sample Output 1
    7
    8
    62
