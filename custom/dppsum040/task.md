# PREFIX040 — Đoạn có tổng đối xứng

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và độ dài $K$. Một đoạn hợp lệ phải gồm **đúng $K$ phần tử liên tiếp**.

Hãy đếm số đoạn có biểu diễn thập phân của tổng đoạn đọc từ trái sang phải và từ phải sang trái giống nhau.

Không thêm chữ số $0$ vào đầu biểu diễn. Số $0$ và các số có một chữ số đều đối xứng.

Hai đoạn khác nhau nếu có vị trí bắt đầu khác nhau. Các đoạn được phép chồng lấn lên nhau. Chỉ xét các đoạn nằm hoàn toàn trong dãy, không nối vòng từ cuối dãy về đầu dãy.

### Dữ liệu vào

- Dòng đầu chứa 2 số nguyên $N,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn dài đúng $K$ thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$.

### Ràng buộc

- $1\le K\le N\le200000$.
- $0\le A_i\le10^9$.

### Sample Input 1

```text
5 2
10 1 21 12 43
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
3 1
0 10 121
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, tổng các đoạn dài đúng $2$ theo thứ tự vị trí bắt đầu là $(11,22,33,55)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,2,3,4)$, nên đáp án là $4$.

Ở ví dụ 2, tổng các đoạn dài đúng $1$ theo thứ tự vị trí bắt đầu là $(0,10,121)$. Các đoạn thỏa điều kiện bắt đầu tại các vị trí $(1,3)$, nên đáp án là $2$.
