# DTDOCHOI — Chia đồ chơi

### Đề bài

Alice và Bob có $n$ đồ chơi. Đồ chơi thứ $i$ có mã màu $c_i$ và kích thước $s_i$. Hai bạn chia toàn bộ đồ chơi thành hai phần, mỗi bạn nhận ít nhất một đồ chơi và mỗi đồ chơi được giao cho đúng một bạn.

Alice quan tâm đến màu sắc. Gọi $c_{\min}$ và $c_{\max}$ lần lượt là mã màu nhỏ nhất và lớn nhất trong phần của Alice. Bob quan tâm đến kích thước. Gọi $s_{\min}$ và $s_{\max}$ lần lượt là kích thước nhỏ nhất và lớn nhất trong phần của Bob.

Hãy tìm cách chia sao cho tổng $(c_{\max}-c_{\min})+(s_{\max}-s_{\min})$ nhỏ nhất.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $n$, số lượng đồ chơi.
- Trong $n$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $c_i$ và $s_i$, lần lượt là mã màu và kích thước của đồ chơi thứ $i$.

### Dữ liệu ra

In một số nguyên là giá trị nhỏ nhất có thể của $(c_{\max}-c_{\min})+(s_{\max}-s_{\min})$.

### Ràng buộc

- $2 \le n \le 2\,000\,000$.
- $0 \le c_i,s_i \le 10^8$ với mọi $1 \le i \le n$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 10% | $n \le 20$ |
| 2 | 20% | $n \le 200$ |
| 3 | 20% | $n \le 2\,000$ |
| 4 | 20% | $n \le 50\,000$ |
| 5 | 20% | $n \le 500\,000$ |
| 6 | 10% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4
0 0
5 5
1 1
3 4
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
4
0 2
5 0
5 9
10 2
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, Alice nhận đồ chơi $1$ và $3$, Bob nhận đồ chơi $2$ và $4$. Tổng chênh lệch là $(1-0)+(5-4)=2$. Vì các mã màu đôi một khác nhau và các kích thước cũng đôi một khác nhau, một phần có $k$ đồ chơi luôn có chênh lệch ít nhất $k-1$ theo đại lượng của người nhận. Tổng chênh lệch vì thế ít nhất là $2$.

Ở ví dụ 2, Alice nhận đồ chơi $2$ và $3$, cùng có mã màu $5$. Bob nhận đồ chơi $1$ và $4$, cùng có kích thước $2$. Tổng chênh lệch bằng $0$.
