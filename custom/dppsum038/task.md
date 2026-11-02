# PREFIX038 — Đoạn có tổng chữ số bằng H

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và độ dài $K$. Một đoạn hợp lệ phải gồm **đúng $K$ phần tử liên tiếp**.

Hãy đếm số đoạn có tổng các chữ số thập phân của tổng đoạn bằng $H$.

Tính tổng các phần tử trước, sau đó mới tính tổng chữ số của kết quả đó. Tổng chữ số của số $0$ bằng $0$.

Hai đoạn khác nhau nếu có vị trí bắt đầu khác nhau. Các đoạn được phép chồng lấn lên nhau. Chỉ xét các đoạn nằm hoàn toàn trong dãy, không nối vòng từ cuối dãy về đầu dãy.

### Dữ liệu vào

- Dòng đầu chứa 3 số nguyên $N,K,H$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn dài đúng $K$ thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$.

### Ràng buộc

- $1\le K\le N\le200000$.
- $0\le A_i\le10^9$.
- $0\le H\le135$.

### Sample Input 1

```text
5 2 6
10 14 1 23 2
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 1 0
0 10 0
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(24,15,24,25)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,2,3)$, nên đáp án là $3$.

Ở ví dụ 2, tổng các đoạn dài đúng $1$ theo thứ tự vị trí bắt đầu là $(0,10,0)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,3)$, nên đáp án là $2$.
