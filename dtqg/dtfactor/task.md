# DTFACTOR — Phân tích thành thừa số

### Đề bài

Cho số nguyên $N>1$ có phân tích ra thừa số nguyên tố dạng

$$N=p_1^k p_2^k\cdots p_m^k,$$

trong đó $p_1,\ldots,p_m$ là các số nguyên tố đôi một khác nhau, $m\ge1$, $k\ge1$. Như vậy, tất cả số mũ trong phân tích nguyên tố của $N$ đều bằng nhau.

Một cách phân tích cần đếm có dạng

$$N=x_1x_2\cdots x_l,\qquad 2\le x_1\le x_2\le\cdots\le x_l,\qquad l\ge2.$$

Hai cách khác nhau nếu hai dãy thừa số khác nhau. Chỉ thay đổi thứ tự các thừa số không tạo ra cách mới. Không tính cách chỉ có một thừa số $N$, và không cho phép thừa số $1$.

Hãy đếm số cách phân tích cho mỗi số $N$ được cho. Kết quả cần in chính xác, không lấy modulo.

### Dữ liệu vào

Đọc từ tệp `factor.INP`:

- Dòng đầu chứa số nguyên $T$ là số bộ dữ liệu.
- Trong $T$ dòng tiếp theo, mỗi dòng chứa một số nguyên $N$.

### Dữ liệu ra

Ghi ra tệp `factor.OUT` $T$ dòng; mỗi dòng là số cách phân tích của bộ dữ liệu tương ứng.

### Ràng buộc

- $1\le T\le150$.
- $2\le N\le10^{12}$.
- Mỗi $N$ có tất cả số mũ trong phân tích nguyên tố bằng nhau. Mỗi bộ có thể có cặp $(m,k)$ khác nhau.

### Sample Input 1

```text
1
64
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
2
30
100
```

### Sample Output 2

```text
4
8
```

### Giải thích

Ở ví dụ 1, $64=2^6$. Các cách phân tích tương ứng với cách chia số mũ $6$ thành tổng các số nguyên dương, bỏ trường hợp chỉ có một phần $6$. Có mười cách.

Ở ví dụ 2, bốn cách của $30$ là $2\cdot3\cdot5$, $2\cdot15$, $3\cdot10$ và $5\cdot6$. Số $100$ có tám cách.

### Nguồn

Chuyển từ `factor.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
