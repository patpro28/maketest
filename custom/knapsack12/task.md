# KNAPSACK12 — Nâng cấp robot

### Đề bài

Robot ban đầu có sức mạnh $S$. Bạn phải lắp cả $N$ linh kiện; linh kiện $i$ phải chạy ở đúng một trong hai chế độ:

- Chế độ thường: cộng thêm $A_i$ sức mạnh.
- Chế độ ép xung: cộng thêm $B_i$ sức mạnh, với $B_i>A_i$.

Bạn được ép xung **tối đa** $K$ linh kiện. Hãy xác định có thể làm cho sức mạnh cuối cùng của robot đúng bằng $X$ hay không.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,S,K,X$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,B_i$.

### Dữ liệu ra

In `YES` nếu đạt được đúng $X$ sức mạnh, ngược lại in `NO`.

### Ràng buộc

- $1\le N\le200$; $0\le K\le N$.
- $0\le S\le10^9$; $0\le X\le10^{12}$.
- $1\le A_i\le10^9$; $1\le B_i-A_i\le100$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $N\le60$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 10 1 21
1 4
2 6
3 8
```

### Sample Output 1

```text
YES
```

### Sample Input 2

```text
3 10 0 17
1 4
2 6
3 8
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, chạy hai linh kiện đầu ở chế độ thường và linh kiện thứ ba ở chế độ ép xung: $10+1+2+8=21$. Ở ví dụ 2, không được ép xung nên sức mạnh chỉ bằng $16$.
