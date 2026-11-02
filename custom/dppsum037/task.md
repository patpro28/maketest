# PREFIX037 — Đoạn có tổng chẵn

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và độ dài $K$. Một đoạn hợp lệ phải gồm **đúng $K$ phần tử liên tiếp**.

Hãy đếm số đoạn có tổng các phần tử trong đoạn là số chẵn.

Số $0$ và các số âm chia hết cho $2$ cũng là số chẵn.

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
1 2 4 3 -1
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 3
-1 0 1
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(3,6,7,2)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(2,4)$, nên đáp án là $2$.

Ở ví dụ 2, tổng các đoạn dài đúng $3$ theo thứ tự vị trí bắt đầu là $(0)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1)$, nên đáp án là $1$.
