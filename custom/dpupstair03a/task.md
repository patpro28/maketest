# DPUPSTAIR03A — Những bước nhảy dài

### Đề bài

Mr T phải leo một cầu thang gồm $n$ bậc, được đánh số từ $1$ đến $n$. Ban đầu ông đứng ở bậc $1$ và muốn đi đến bậc $n$.

Mỗi lần bước, Mr T có thể đi lên $1$ bậc hoặc $2$ bậc, nhưng không được đi vượt quá bậc $n$. Có $k$ bậc bị trơn. Nếu đang đứng ở một bậc trơn thì ở bước tiếp theo, ông **không được phép nhảy $2$ bậc**; ông vẫn được đi lên $1$ bậc. Các bậc trơn không phải bậc cấm: Mr T được phép đặt chân lên chúng.

Hãy đếm số cách để Mr T đi từ bậc $1$ đến bậc $n$ sao cho ông thực hiện **đúng $m$ lần nhảy $2$ bậc**.

Hai cách đi khác nhau nếu dãy số hiệu các bậc được đặt chân lên khác nhau. Kết quả cần lấy modulo $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $n,k,m$, trong đó $k$ là số bậc trơn và $m$ là số lần nhảy $2$ bậc cần thực hiện.
- Dòng thứ hai chứa $k$ số nguyên phân biệt $b_1,b_2,\ldots,b_k$ là số hiệu các bậc trơn, không nhất thiết được sắp xếp. Nếu $k=0$, dòng này để trống.

### Dữ liệu ra

In một số nguyên là số cách đi thỏa mãn yêu cầu, lấy modulo $10^9+7$. Nếu không có cách nào, in $0$.

### Ràng buộc

- $2\le n\le10^5$.
- $0\le k<n$.
- $0\le m\le30$.
- $1\le b_i\le n$ với mọi $1\le i\le k$; các $b_i$ đôi một khác nhau.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 30% | $n\le20$ |
| 2 | 20% | $m=0$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
6 3 1
2 4 5
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
5 0 2

```

### Sample Output 2

```text
1
```

### Sample Input 3

```text
3 1 1
1
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, có hai cách hợp lệ và thực hiện đúng một lần nhảy $2$ bậc:

- $1\to2\to3\to5\to6$.
- $1\to3\to4\to5\to6$.

Ở ví dụ 2, không có bậc trơn. Để thực hiện đúng hai lần nhảy $2$ bậc từ bậc $1$ đến bậc $5$, chỉ có cách $1\to3\to5$.

Ở ví dụ 3, bậc $1$ bị trơn nên không được nhảy thẳng từ $1$ đến $3$. Cách $1\to2\to3$ không có lần nhảy $2$ bậc nào, nên kết quả là $0$.
