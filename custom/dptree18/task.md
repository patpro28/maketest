# DPTREE18 — Khu vườn có lợi nhuận lớn nhất

### Đề bài

Một khu vườn gồm $N$ mảnh đất, được đánh số từ $1$ đến $N$. Có $N-1$ lối đi nối các mảnh đất và tạo thành một cây. Mảnh đất thứ $i$ có lợi nhuận $A_i$; giá trị âm biểu thị khoản lỗ.

Bạn muốn chọn một tập mảnh đất **không rỗng và liên thông**. Cụ thể, với hai mảnh đất bất kỳ được chọn, tất cả các mảnh đất trên đường đi duy nhất nối chúng cũng phải được chọn. Lợi nhuận của tập được chọn là tổng lợi nhuận của các mảnh đất thuộc tập đó.

Hãy tìm lợi nhuận lớn nhất có thể đạt được. Bạn được chọn một mảnh đất duy nhất và không bắt buộc chọn mảnh đất số $1$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một lối đi nối hai mảnh đất $u$ và $v$.

### Dữ liệu ra

In một số nguyên là tổng lợi nhuận lớn nhất của một tập mảnh đất không rỗng và liên thông.

### Ràng buộc

- $1\le N\le 2\cdot 10^5$.
- $-10^9\le A_i\le 10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các lối đi tạo thành một cây.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
-10 4 -2 7 5
1 2
1 3
2 4
2 5
```

### Sample Output 1

```text
16
```

### Sample Input 2

```text
3
-5 -2 -7
1 2
2 3
```

### Sample Output 2

```text
-2
```

### Giải thích

Ở ví dụ 1, chọn các mảnh đất $2,4,5$. Chúng liên thông và có tổng lợi nhuận $4+7+5=16$.

Ở ví dụ 2, chọn riêng mảnh đất số $2$ có lợi nhuận $-2$. Không được chọn tập rỗng nên đáp án không phải là $0$.
