# DPTREE36 — Trang trí một nhánh liên thông

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$, có gốc là đỉnh $1$.

Bạn muốn chọn một tập đỉnh để trang trí. Tập được chọn phải **chứa đỉnh $1$ và liên thông**: với hai đỉnh bất kỳ thuộc tập, mọi đỉnh trên đường đi duy nhất nối chúng cũng phải thuộc tập.

Hãy đếm số cách chọn hợp lệ. Hai cách khác nhau nếu tồn tại một đỉnh được chọn trong cách này nhưng không được chọn trong cách kia. Có thể chọn riêng đỉnh $1$, nhưng không được chọn tập rỗng.

Vì số cách có thể rất lớn, hãy in kết quả lấy dư cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây.

### Dữ liệu ra

In một số nguyên là số tập đỉnh liên thông chứa đỉnh $1$, lấy dư cho $10^9+7$.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây có gốc $1$.

### Sample Input 1

```text
4
1 2
1 3
1 4
```

### Sample Output 1

```text
8
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
4
```

### Giải thích

Ở ví dụ 1, luôn chọn đỉnh $1$. Với mỗi đỉnh trong $\{2,3,4\}$, có thể chọn hoặc không, nên có $2^3=8$ cách.

Ở ví dụ 2, các tập hợp lệ là $\{1\}$, $\{1,2\}$, $\{1,2,3\}$ và $\{1,2,3,4\}$. Không được chọn $\{1,3\}$ vì thiếu đỉnh $2$ trên đường nối hai đỉnh.
