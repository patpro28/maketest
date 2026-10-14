# KNAPSACK24 — Một phiếu giảm giá

### Đề bài

Có $N$ loại sản phẩm. Mỗi sản phẩm loại $i$ có giá $C_i$ và đem lại $V_i$ điểm thưởng; số lượng mỗi loại không giới hạn.

Bạn phải dùng **đúng một phiếu giảm giá** cho đúng một sản phẩm được mua. Sản phẩm đó giữ nguyên điểm thưởng nhưng giá giảm còn $\lfloor C_i/2\rfloor$. Mọi sản phẩm khác trả đủ giá.

Với ngân sách tối đa $W$, hãy tìm tổng điểm thưởng lớn nhất. Nếu không thể mua một sản phẩm có dùng phiếu trong ngân sách, hãy báo không thể. Khi $C_i=1$, sản phẩm dùng phiếu có giá $0$, nhưng chỉ một sản phẩm được hưởng ưu đãi.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,W$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $C_i,V_i$.

### Dữ liệu ra

In tổng điểm thưởng lớn nhất; in `-1` nếu không có phương án hợp lệ.

### Ràng buộc

- $1\le N\le100$; $0\le W\le10000$.
- $1\le C_i\le20000$; $1\le V_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $W\le20$ |
| 2 | 30% | $W\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 5
3 5
2 3
```

### Sample Output 1

```text
11
```

### Sample Input 2

```text
1 0
2 7
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, mua một sản phẩm loại thứ nhất với phiếu và hai sản phẩm loại thứ hai: giá $1+2+2=5$, điểm $5+3+3=11$. Ở ví dụ 2, giá sau giảm vẫn bằng $1$, vượt ngân sách $0$.
