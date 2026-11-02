# PREFIX036 — Đoạn có tổng cho phần dư C

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và độ dài $K$. Một đoạn hợp lệ phải gồm **đúng $K$ phần tử liên tiếp**.

Hãy đếm số đoạn có tổng các phần tử trong đoạn khi chia cho $M$ có phần dư bằng $C$.

Hai đoạn khác nhau nếu có vị trí bắt đầu khác nhau. Các đoạn được phép chồng lấn lên nhau. Chỉ xét các đoạn nằm hoàn toàn trong dãy, không nối vòng từ cuối dãy về đầu dãy.

### Dữ liệu vào

- Dòng đầu chứa 4 số nguyên $N,K,M,C$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn dài đúng $K$ thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$.

### Ràng buộc

- $1\le K\le N\le200000$.
- $0\le A_i\le10^9$.
- $1\le M\le10^9$.
- $0\le C<M$.

### Sample Input 1

```text
5 2 4 1
1 4 1 3 2
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 1 1 0
0 10 3
```

### Sample Output 2

```text
3
```

### Giải thích

Ở ví dụ 1, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(5,5,4,5)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,2,4)$, nên đáp án là $3$.

Ở ví dụ 2, tổng các đoạn dài đúng $1$ theo thứ tự vị trí bắt đầu là $(0,10,3)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,2,3)$, nên đáp án là $3$.
