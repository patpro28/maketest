### Đề bài

Cho một đơn đồ thị **có hướng** gồm $n$ đỉnh và $m$ cạnh. Mỗi cạnh có trọng số là một số nguyên dương. Sắp xếp các cạnh của đồ thị theo trọng số tăng dần. Nếu hai cạnh có trọng số bằng nhau, sắp xếp theo thứ tự đỉnh đầu tiên, sau đó là đỉnh thứ hai.

### Dữ liệu vào

- Dòng đầu tiên chứa hai số nguyên $n$ và $m$ ($1 \leq n \leq 10^5$, $n \leq m \leq 10^5$) là số đỉnh và số cạnh của đồ thị.
- Mỗi trong $m$ dòng tiếp theo chứa ba số nguyên $u$, $v$, $w$ ($1 \leq u, v \leq n$, $u \neq v$, $1 \leq w \leq 10^6$) mô tả một cạnh từ đỉnh $u$ đến đỉnh $v$ với trọng số $w$.

### Dữ liệu ra

- In ra $m$ dòng, mỗi dòng chứa ba số nguyên $u$, $v$, $w$ của một cạnh, theo thứ tự đã sắp xếp.

### Sample Input

```
5 7
1 2 3
1 3 1
2 3 2
2 4 7
2 5 5
3 5 7
4 5 6
```

### Sample Output

```
1 3 1
2 3 2
1 2 3
2 5 5
4 5 6
2 4 7
3 5 7
```
