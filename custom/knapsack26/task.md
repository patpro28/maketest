# KNAPSACK26 — Mở dây chuyền rồi sản xuất

### Đề bài

Có $N$ dây chuyền. Muốn sản xuất trên dây chuyền $i$, bạn phải trả phí mở $F_i$ đúng một lần. Sau khi mở, mỗi sản phẩm trên dây chuyền này tốn thêm $C_i$ và đem lại $V_i$ lợi nhuận. Số sản phẩm mỗi dây chuyền có thể làm không giới hạn.

Với ngân sách tối đa $W$, hãy tìm tổng lợi nhuận lớn nhất. Có thể không mở dây chuyền nào. Nếu sản xuất $k_i>0$ sản phẩm trên dây chuyền $i$, tổng chi phí của dây chuyền là $F_i+k_iC_i$; nếu không sản xuất thì không phải trả phí mở.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,W$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $F_i,C_i,V_i$.

### Dữ liệu ra

In tổng lợi nhuận lớn nhất.

### Ràng buộc

- $1\le N\le200$; $0\le W\le20000$.
- $0\le F_i\le20000$; $1\le C_i\le20000$; $1\le V_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $W\le20$ |
| 2 | 30% | $W\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 10
4 2 5
0 3 4
```

### Sample Output 1

```text
15
```

### Sample Input 2

```text
1 3
4 1 10
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, mở dây chuyền thứ nhất rồi làm ba sản phẩm: chi phí $4+3\cdot2=10$, lợi nhuận $15$. Ở ví dụ 2, riêng phí mở đã vượt ngân sách nên không sản xuất.
