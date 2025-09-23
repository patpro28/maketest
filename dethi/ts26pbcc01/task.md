### Đề bài

Bình rất yêu thích các số đặc biệt. Gọi một số nguyên dương $X$ là **số thú vị** nếu hai chữ số tận cùng của $X$ tạo thành một số chia hết cho số nguyên dương $k$ cho trước.

Ví dụ:

- Với $k = 12$, số $1236$ là số thú vị vì hai chữ số cuối là $36$ chia hết cho $12$.
- Số $1457$ không phải là số thú vị vì $57$ không chia hết cho $12$.

Bình muốn đếm số lượng số thú vị trong đoạn $[a, b]$. Hãy viết chương trình giúp Bình.

### Dữ liệu vào

- Dòng đầu gồm hai số nguyên $T$ và $k$ — số lượng truy vấn và số chia kiểm tra. $(1 \leq T \leq 10^5, 1 \leq k \leq 99)$
- $T$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $a$ và $b$ là đoạn cần xét. $(10^2 \leq a \leq b \leq 10^{18})$

### Dữ liệu ra

Ghi ra $T$ dòng, mỗi dòng là số lượng số thú vị trong đoạn tương ứng $[a, b]$.

### Giới hạn

- 50% số test có $T = 1$, $10^2 \leq a \leq b \leq 10^6$
- 40% số test có $T \leq 10^5$, $10^2 \leq a \leq b \leq 10^6$
- 10% số test có $T \leq 10^5$, $10^2 \leq a \leq b \leq 10^{18}$

### Sample Input

```
2 11
100 200
201 300
```

### Sample Output

```
11
10
```

### Giải thích

- Trong đoạn $[100, 200]$ có 11 số mà hai chữ số tận cùng chia hết cho 11.
- Trong đoạn $[201, 300]$ có 10 số như vậy.
