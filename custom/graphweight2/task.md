### Đề bài

Cho một đơn đồ thị **có hướng** gồm $n$ đỉnh và $m$ cạnh. Mỗi cạnh có trọng số là một số nguyên dương.

Có $q$ truy vấn, mỗi truy vấn yêu cầu xác định số lượng cạnh xuất phát từ một đỉnh $u$ và có trọng số lớn hơn hoặc bằng $w$.

### Dữ liệu vào

- Dòng đầu tiên chứa hai số nguyên $n$ và $m$ ($1 \leq n \leq 50000$, $n \leq m \leq 5\times 10^5$) là số đỉnh và số cạnh của đồ thị.
- Mỗi trong $m$ dòng tiếp theo chứa ba số nguyên $u$, $v$, $w$ ($1 \leq u, v \leq n$, $u \neq v$, $1 \leq w \leq 10^6$) mô tả một cạnh từ đỉnh $u$ đến đỉnh $v$ với trọng số $w$.
- Dòng tiếp theo chứa một số nguyên $q$ ($1 \leq q \leq 200$) là số lượng truy vấn.
- Mỗi trong $q$ dòng tiếp theo chứa hai số nguyên $u$ và $w$ ($1 \leq u \leq n$, $1 \leq w \leq 10^6$) mô tả truy vấn yêu cầu xác định số lượng cạnh xuất phát từ đỉnh $u$ có trọng số lớn hơn hoặc bằng $w$.

### Dữ liệu ra

- In ra $q$ dòng, mỗi dòng chứa một số nguyên là kết quả của truy vấn tương ứng.

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
3
1 2
2 5
3 8
```

### Sample Output

```
1
2
0
```
