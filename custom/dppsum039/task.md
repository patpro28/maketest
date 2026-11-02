# PREFIX039 — Đoạn có tổng chính phương

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và độ dài $K$. Một đoạn hợp lệ phải gồm **đúng $K$ phần tử liên tiếp**.

Hãy đếm số đoạn có tổng các phần tử trong đoạn là số chính phương, nghĩa là bằng $x^2$ với một số nguyên không âm $x$.

Số $0$ là số chính phương. Tổng âm không phải số chính phương.

Hai đoạn khác nhau nếu có vị trí bắt đầu khác nhau. Các đoạn được phép chồng lấn lên nhau. Chỉ xét các đoạn nằm hoàn toàn trong dãy, không nối vòng từ cuối dãy về đầu dãy.

### Dữ liệu vào

- Dòng đầu chứa 2 số nguyên $N,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn dài đúng $K$ thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$.

### Ràng buộc

- $1\le K\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
5 2
1 3 6 10 -1
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
3 3
-2 0 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(4,9,16,9)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,2,3,4)$, nên đáp án là $4$.

Ở ví dụ 2, tổng các đoạn dài đúng $3$ theo thứ tự vị trí bắt đầu là $(-1)$. Không đoạn nào thỏa điều kiện nên đáp án là $0$.
