# DPUPSTAIR03B — Đi qua bậc trơn

### Đề bài

Mr T phải leo một cầu thang gồm $n$ bậc, được đánh số từ $1$ đến $n$. Ban đầu ông đứng ở bậc $1$ và muốn đi đến bậc $n$.

Mỗi lần bước, Mr T có thể đi lên $1$ bậc hoặc $2$ bậc, nhưng không được đi vượt quá bậc $n$. Có $k$ bậc bị trơn. Nếu đang đứng ở một bậc trơn thì ở bước tiếp theo, ông **không được phép nhảy $2$ bậc**; ông vẫn được đi lên $1$ bậc. Các bậc trơn không phải bậc cấm: Mr T được phép đặt chân lên chúng.

Hãy đếm số cách để Mr T đi từ bậc $1$ đến bậc $n$ sao cho ông **đặt chân lên đúng $m$ bậc trơn trong quá trình di chuyển**.

**Không tính bậc xuất phát $1$**, dù bậc này bị trơn. Nếu bậc $n$ bị trơn thì vẫn tính bậc này khi Mr T đi đến đó. Bậc trơn bị nhảy qua không được tính. Vì chỉ đi lên, mỗi bậc được đặt chân lên nhiều nhất một lần.

Hai cách đi khác nhau nếu dãy số hiệu các bậc được đặt chân lên khác nhau. Kết quả cần lấy modulo $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $n,k,m$, trong đó $k$ là số bậc trơn và $m$ là số bậc trơn cần đặt chân lên, không tính bậc xuất phát.
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
6 3 2
2 4 5
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 2 1
1 3
```

### Sample Output 2

```text
1
```

### Sample Input 3

```text
5 0 0

```

### Sample Output 3

```text
5
```

### Giải thích

Ở ví dụ 1, có hai cách hợp lệ và đặt chân lên đúng hai bậc trơn:

- $1\to2\to3\to5\to6$: các bậc trơn được tính là $2,5$.
- $1\to3\to4\to5\to6$: các bậc trơn được tính là $4,5$.

Ở ví dụ 2, bậc $1$ trơn nên không được nhảy thẳng lên bậc $3$. Chỉ có đường đi $1\to2\to3$; bậc $1$ không được tính, còn bậc $3$ được tính, nên đường đi đặt chân lên đúng một bậc trơn.

Ở ví dụ 3, không có bậc trơn và $m=0$. Có năm cách đi là $1\to2\to3\to4\to5$, $1\to2\to3\to5$, $1\to2\to4\to5$, $1\to3\to4\to5$ và $1\to3\to5$.
