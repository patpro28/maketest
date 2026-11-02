# PREFIX050 — Tổng nhỏ nhất, vị trí và số lượng

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, đánh số vị trí từ $1$, và độ dài $K$.

Xét các đoạn gồm đúng $K$ phần tử liên tiếp. Hãy tìm tổng nhỏ nhất, vị trí bắt đầu lớn nhất trong các đoạn đạt tổng đó, và tổng số đoạn đạt tổng đó.

Các đoạn phải nằm hoàn toàn trong dãy, không nối vòng. Các đoạn được phép chồng lấn. Hai đoạn khác nhau nếu có vị trí bắt đầu khác nhau. Bạn bắt buộc chọn đoạn dài đúng $K$, kể cả khi các phần tử đều âm.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In ba số nguyên trên một dòng theo thứ tự: tổng nhỏ nhất, vị trí bắt đầu lớn nhất trong các đoạn đạt tổng đó, số lượng các đoạn đạt tổng đó.

### Ràng buộc

- $1\le K\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
6 2
-3 5 -1 4 0 -2
```

### Sample Output 1

```text
-2 5 1
```

### Sample Input 2

```text
5 2
-2 -2 -2 -2 -2
```

### Sample Output 2

```text
-4 4 4
```

### Giải thích

Ở ví dụ 1, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(2,4,3,4,-2)$. Tổng nhỏ nhất bằng $-2$, đạt tại các vị trí bắt đầu $(5)$. Vị trí lớn nhất là $5$. Có $1$ đoạn đạt tổng này.

Ở ví dụ 2, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(-4,-4,-4,-4)$. Tổng nhỏ nhất bằng $-4$, đạt tại các vị trí bắt đầu $(1,2,3,4)$. Vị trí lớn nhất là $4$. Có $4$ đoạn đạt tổng này.
