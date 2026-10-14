# KNAPSACK25 — Sản xuất bằng hai nguyên liệu

### Đề bài

Xưởng có $X$ đơn vị kim loại và $Y$ đơn vị nhựa. Có $N$ loại sản phẩm. Mỗi sản phẩm loại $i$ dùng $A_i$ kim loại và $B_i$ nhựa, đem lại $V_i$ lợi nhuận.

Số lượng sản phẩm mỗi loại được sản xuất không giới hạn. Hãy tìm tổng lợi nhuận lớn nhất mà không vượt lượng có sẵn của **cả hai** nguyên liệu. Có thể không sản xuất sản phẩm nào.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,X,Y$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $A_i,B_i,V_i$.

### Dữ liệu ra

In tổng lợi nhuận lớn nhất.

### Ràng buộc

- $1\le N\le40$; $0\le X,Y\le200$.
- $1\le A_i,B_i\le200$; $1\le V_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $X,Y\le10$ |
| 2 | 30% | $X,Y\le50$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 5 5
1 2 3
2 1 4
```

### Sample Output 1

```text
11
```

### Sample Input 2

```text
1 0 5
1 1 7
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, làm một sản phẩm loại thứ nhất và hai sản phẩm loại thứ hai: dùng $5$ kim loại, $4$ nhựa, lợi nhuận $11$. Ở ví dụ 2, không có kim loại nên không sản xuất được sản phẩm nào.
