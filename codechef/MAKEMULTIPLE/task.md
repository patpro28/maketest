### Đề bài

Cho một chuỗi nhị phân $S$.

Trong mỗi giây, các bit có giá trị $1$ trong chuỗi sẽ thực hiện **đồng thời** và **độc lập** các hành động sau:

- Biến bit từ $1$ thành $0$.
- Nếu hàng xóm bên trái tồn tại và là $0$, thì biến nó thành $1$.
- Nếu hàng xóm bên phải tồn tại và là $0$, thì biến nó thành $1$.

Ví dụ, nếu ban đầu $S = 010$, sau 1 giây thì $S = 101$ (bit $1$ và hai hàng xóm đều bị thay đổi). Sau 1 giây nữa thì $S = 010$ (bit đầu và cuối bị chuyển về $0$ do trước đó là $1$, còn bit giữa là hàng xóm của $1$ nên chuyển thành $1$).

**Yêu cầu:** Tìm chuỗi $S$ sau đúng $K$ giây.

### Dữ liệu vào

- Dòng đầu tiên chứa số nguyên $T$ — số lượng test.
- Mỗi test bao gồm:
    - Một dòng chứa hai số nguyên cách nhau $N$ và $K$ — độ dài chuỗi và số giây.
    - Một dòng chứa chuỗi nhị phân $S$ gồm $N$ ký tự.

### Dữ liệu ra

Với mỗi test, in ra chuỗi $S$ sau đúng $K$ giây.

### Giới hạn

- $1 \leq T \leq 1000$
- $1 \leq N \leq 10^5$
- $0 \leq K \leq 10^9$
- Tổng độ dài chuỗi của tất cả các test không vượt quá $10^6$

### Sample Input 1

    3
    3 1
    101
    5 2
    10001
    14 3
    10011010111000

### Sample Output 1

    010
    10101
    01100101010101

### Giải thích

- Ở test thứ hai: Sau 1 giây, $S = 01010$. Sau 1 giây nữa, các bit $1$ chuyển thành $0$, các hàng xóm $0$ thành $1 ⇒ S = 10101$.
