# DPTREE25 — Chọn người đại diện

### Đề bài

Một tổ chức có $N$ người, được đánh số từ $1$ đến $N$. Quan hệ quản lý được biểu diễn bởi một cây có gốc là người số $1$.

Với hai người phân biệt $u,v$, người $u$ là **tổ tiên** của người $v$ nếu $u$ nằm trên đường đi từ gốc $1$ đến $v$. Vì hai người phải phân biệt, một người không được xem là tổ tiên của chính mình.

Bạn cần chọn một tập người đại diện sao cho **không người nào được chọn là tổ tiên của một người được chọn khác**. Điều kiện áp dụng cho mọi cấp tổ tiên, không chỉ người quản lý trực tiếp.

Hãy đếm số cách chọn, kể cả cách không chọn ai. Hai cách khác nhau nếu tồn tại một người được chọn trong cách này nhưng không được chọn trong cách kia. In kết quả lấy dư cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây tổ chức. Gốc của cây luôn là đỉnh $1$.

### Dữ liệu ra

In một số nguyên là số cách chọn người đại diện hợp lệ, lấy dư cho $10^9+7$.

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
4
```

### Sample Input 2

```text
4
1 2
1 3
1 4
```

### Sample Output 2

```text
9
```

### Giải thích

Ở ví dụ 1, các cách hợp lệ là $\varnothing$, $\{1\}$, $\{2\}$ và $\{3\}$. Không được chọn đồng thời $1$ và $3$ dù hai đỉnh không kề nhau, vì $1$ là tổ tiên của $3$.

Ở ví dụ 2, nếu chọn người $1$ thì không được chọn ai khác, có $1$ cách. Nếu không chọn người $1$, có thể chọn tùy ý một tập con của $\{2,3,4\}$, có $2^3=8$ cách. Tổng cộng có $9$ cách.
