### Đề bài

Cho hai mảng $a$ và $b$ có cùng kích thước. Gọi đa tập các phần tử của $a$ và $b$ lần lượt là $M_A$ và $M_B$.

Hai mảng $a$ và $b$ được gọi là *đẳng cấu* (isomorphic) nếu tồn tại một song ánh $f: \mathbb{Z} \to \mathbb{Z}$ sao cho:

- Với mỗi phần tử $x$ xuất hiện trong $M_A$, ta thêm $f(x)$ vào một đa tập mới $M_F$.
- Đa tập $M_F$ thu được phải giống hệt với $M_B$.

Ví dụ: $M_A=\{1,1,2,2,2,3\}$ và $M_B=\{3,3,4,9,9,9\}$ thì ta có thể chọn $f(1)=3, f(2)=9, f(3)=4$. Khi đó sau khi biến đổi ta được $M_F=\{3,3,9,9,9,4\}=M_B$ nên hai mảng là đẳng cấu.

Giờ bạn có mảng $a$ kích thước $n$ và có $q$ truy vấn. Mỗi truy vấn cho hai đoạn con:
- $a_x, a_{x+1}, \ldots, a_y$
- $a_z, a_{z+1}, \ldots, a_t$

với điều kiện $y-x = t-z$. Ta cần kiểm tra hai đoạn con có đẳng cấu hay không.

Chỉ số $y$ và $t$ được sinh theo quy tắc sau:

- Gọi $k = \min(n-x, n-z) + 1$.
- Gọi $last$ là chỉ số của truy vấn gần nhất có kết quả "YES" (nếu chưa có thì $last = 0$).
- $y = x + (c + d \cdot last) \bmod k$
- $t = z + (c + d \cdot last) \bmod k$

### Dữ liệu vào

- Dòng đầu: số nguyên $T$ — số test.
- Với mỗi test:
    - Một dòng chứa số nguyên $n$.
    - Một dòng chứa $n$ số nguyên $a_1, a_2, \ldots, a_n$.
    - Một dòng chứa số nguyên $q$.
    - $q$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên $x, z, c, d$.

### Dữ liệu ra

Với mỗi truy vấn, in ra `"YES"` nếu hai đoạn con là đẳng cấu, ngược lại in `"NO"`.

### Ràng buộc

- $1 \le T \le 10$
- $1 \le n \le 75\,000$
- $1 \le q \le 2 \cdot 10^5$
- $1 \le a_i \le n$
- $1 \le x, z \le n$
- $0 \le c, d \le 10^9$
- Tổng $n$ trên tất cả test $\le 150\,000$
- Tổng $q$ trên tất cả test $\le 4 \cdot 10^5$

### Sample Input 1
    1
    5
    2 1 2 3 3
    5
    2 1 3 0
    1 2 2 0
    2 4 2 4
    3 5 1 3
    2 5 2 5

### Sample Output 1
    YES
    NO
    YES
    YES
    YES

### Giải thích

- Truy vấn 1: $last=0$, $y=5$, $t=4$.
- Truy vấn 2: $last=1$, $y=3$, $t=4$.
- Truy vấn 3: $last=1$, $y=2$, $t=4$.
- Truy vấn 4: $last=3$, $y=3$, $t=5$.
- Truy vấn 5: $last=4$, $y=2$, $t=5$.

