# DPTREE26 — Đếm cách ghép đôi

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$.

Một cách ghép đôi là một tập cạnh sao cho **không có hai cạnh được chọn chung một đầu mút**. Bạn được phép chọn tập rỗng.

Hãy đếm số cách ghép đôi của cây. Hai cách được xem là khác nhau nếu tồn tại một cạnh được chọn trong cách này nhưng không được chọn trong cách kia. Đếm tất cả các cách hợp lệ, không chỉ những cách có số cạnh lớn nhất.

Vì kết quả có thể rất lớn, hãy in số cách lấy dư cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh nối hai đỉnh $u$ và $v$.

### Dữ liệu ra

In một số nguyên là số cách ghép đôi của cây, lấy dư cho $10^9+7$.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây.

### Sample Input 1

```text
3
1 2
2 3
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4
1 2
2 3
3 4
```

### Sample Output 2

```text
5
```

### Giải thích

Ở ví dụ 1, có ba cách: không chọn cạnh nào, chọn riêng cạnh $(1,2)$, hoặc chọn riêng cạnh $(2,3)$. Không được chọn cả hai cạnh vì chúng chung đầu mút $2$.

Ở ví dụ 2, có một cách chọn tập rỗng, ba cách chọn đúng một cạnh và một cách chọn hai cạnh $(1,2)$, $(3,4)$. Tổng cộng có $5$ cách.
