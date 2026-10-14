# DPKSET — Bỏ một hệ số

### Đề bài

Cho dãy số nguyên $x_1,x_2,\ldots,x_n$ và $k$ hệ số nguyên $a_1,a_2,\ldots,a_k$.

Một phương án được thực hiện như sau:

- Bỏ đi đúng một trong $k$ hệ số.
- Giữ nguyên thứ tự của $k-1$ hệ số còn lại.
- Chọn $k-1$ chỉ số $1\le i_1<i_2<\ldots<i_{k-1}\le n$.

Giả sử sau khi bỏ một hệ số, các hệ số còn lại theo thứ tự là $b_1,b_2,\ldots,b_{k-1}$. Trọng số của phương án được xác định bằng:

$$b_1x_{i_1}+b_2x_{i_2}+\cdots+b_{k-1}x_{i_{k-1}}.$$

Hai phương án được xem là khác nhau nếu hệ số bị bỏ nằm ở hai vị trí khác nhau hoặc tồn tại ít nhất một vị trí chỉ số được chọn khác nhau.

Hãy xác định trọng số lớn nhất có thể đạt được và số phương án đạt được trọng số lớn nhất đó. Vì số phương án có thể rất lớn, hãy tính **số phương án** theo modulo $10^9+7$; trọng số lớn nhất được in chính xác.

Khi $k=1$, bỏ hệ số duy nhất và không chọn chỉ số nào. Có đúng một phương án với trọng số bằng $0$.

### Dữ liệu vào

- Dòng đầu tiên chứa hai số nguyên $n,k$.
- Dòng thứ hai chứa $k$ số nguyên $a_1,a_2,\ldots,a_k$.
- Dòng thứ ba chứa $n$ số nguyên $x_1,x_2,\ldots,x_n$.

### Dữ liệu ra

In ra hai số nguyên trên một dòng, lần lượt là trọng số lớn nhất có thể đạt được và số phương án đạt trọng số lớn nhất, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le k\le n\le 2\cdot10^5$.
- $1\le k\le100$.
- $|a_i|\le100$ với mọi $1\le i\le k$.
- $|x_i|\le10^9$ với mọi $1\le i\le n$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $n\le20$ |
| 2 | 20% | $n\le200$ |
| 3 | 20% | $n\le5000$ |
| 4 | 20% | Các hệ số $a_1,a_2,\ldots,a_k$ đôi một khác nhau |
| 5 | 20% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
7 6
1 -1 3 1 -1 1
2 8 1 9 1 -1 8
```

### Sample Output 1

```text
45 1
```

### Giải thích

Bỏ hệ số thứ hai, có giá trị $-1$. Khi đó, năm hệ số còn lại theo thứ tự là $1,3,1,-1,1$.

Chọn bộ chỉ số $(2,4,5,6,7)$. Trọng số của phương án này là:

$$1\cdot8+3\cdot9+1\cdot1+(-1)\cdot(-1)+1\cdot8=45.$$

Đây là trọng số lớn nhất và chỉ có một phương án đạt được kết quả này.

Các phương án được phân biệt theo vị trí của hệ số bị bỏ. Do đó, nếu hai hệ số có cùng giá trị nhưng nằm ở hai vị trí khác nhau thì việc bỏ từng hệ số vẫn tạo thành hai phương án khác nhau.
