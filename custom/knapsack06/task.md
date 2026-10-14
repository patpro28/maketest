# KNAPSACK06 — Ghép đoạn dây đạt đúng độ dài

### Đề bài

Có $N$ loại đoạn dây, mỗi đoạn thuộc loại $i$ dài $A_i$. Mỗi loại có số lượng **không giới hạn**.

Bạn được lấy các đoạn dây rồi nối chúng lại. Chiều dài đoạn dây sau khi nối là tổng chiều dài của các đoạn đã lấy. Không được cắt đoạn dây, nhưng có thể lấy nhiều đoạn cùng loại.

Hãy xác định có thể ghép được một đoạn dây dài **đúng bằng** $X$ hay không. Khi $X=0$, được phép không lấy đoạn nào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In `YES` nếu ghép được đúng chiều dài $X$, ngược lại in `NO`.

### Ràng buộc

- $1\le N\le100$; $0\le X\le10000$.
- $1\le A_i\le10000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $X\le20$ |
| 2 | 30% | $X\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 12
4 7
```

### Sample Output 1

```text
YES
```

### Sample Input 2

```text
2 5
4 6
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, lấy ba đoạn loại thứ nhất để được $4+4+4=12$. Ở ví dụ 2, các đoạn dây đều có chiều dài chẵn nên không thể ghép được chiều dài $5$.
