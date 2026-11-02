# PREFIX056 — Nhiều số chính phương nhất

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, đánh số từ $1$, và độ dài $K$.

Hãy tìm một đoạn gồm **đúng $K$ phần tử liên tiếp** có số lượng phần tử thỏa điều kiện sau nhiều nhất: $A_i=x^2$ với một số nguyên không âm $x$.

Số $0$ là số chính phương. Các số âm không phải số chính phương.

Nếu có nhiều đoạn cùng đạt số lượng lớn nhất, chọn đoạn có vị trí bắt đầu nhỏ nhất. In số lượng lớn nhất và vị trí bắt đầu của đoạn được chọn. Nếu không có phần tử nào thỏa điều kiện trong toàn bộ dãy, kết quả là $0$ và vị trí $1$.

Chỉ xét các đoạn nằm hoàn toàn trong dãy, không nối vòng. Các đoạn được phép chồng lấn. Các phần tử có cùng giá trị ở những vị trí khác nhau được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa 2 số nguyên $N,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In hai số nguyên trên một dòng theo thứ tự: số lượng phần tử thỏa điều kiện nhiều nhất trong một đoạn dài đúng $K$, rồi đến vị trí bắt đầu nhỏ nhất của đoạn đạt số lượng đó.

### Ràng buộc

- $1\le K\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
7 3
-1 2 0 4 3 9 5
```

### Sample Output 1

```text
2 2
```

### Sample Input 2

```text
4 2
-1 2 3 5
```

### Sample Output 2

```text
0 1
```

### Giải thích

Ở ví dụ 1, số phần tử thỏa điều kiện trong các đoạn dài đúng $3$ theo thứ tự vị trí bắt đầu là $(1,2,2,2,1)$. Số lượng lớn nhất bằng $2$; vị trí bắt đầu nhỏ nhất đạt số lượng đó là $2$.

Ở ví dụ 2, số phần tử thỏa điều kiện trong các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(0,0,0)$. Số lượng lớn nhất bằng $0$; vị trí bắt đầu nhỏ nhất đạt số lượng đó là $1$.
