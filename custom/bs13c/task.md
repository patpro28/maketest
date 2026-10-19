# BS13C — Chọn phòng phù hợp

### Đề bài

Một khách sạn có $N$ phòng. Phòng thứ $i$ có sức chứa $A_i$ người. Các phòng được xem là khác nhau, kể cả khi có cùng sức chứa.

Có $Q$ đoàn khách cần được tư vấn. Một đoàn gồm $X$ người phải ở chung trong đúng một phòng có sức chứa ít nhất $X$. Nếu chọn phòng có sức chứa $A_i$, số chỗ trống là $A_i-X$.

Với mỗi đoàn, hãy tìm số chỗ trống nhỏ nhất có thể và đếm số phòng đạt được số chỗ trống đó. Nếu không có phòng phù hợp, báo không có phương án.

Các đoàn được xét độc lập, dựa trên cùng danh sách phòng ban đầu. Việc xét một đoàn không làm mất đi phòng nào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$. Các số không nhất thiết được sắp xếp.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa một số nguyên $X$ là số người của một đoàn.

### Dữ liệu ra

In $Q$ dòng theo thứ tự truy vấn. Nếu có phòng phù hợp, in hai số nguyên: số chỗ trống nhỏ nhất và số phòng đạt mức đó. Nếu không có phòng phù hợp, in `-1 0`.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $1\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le X\le10^9$ trong mỗi truy vấn.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 50% | $N\cdot Q\le10^6$ |
| 2 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 4
8 3 5 5 10
4
8
11
1
```

### Sample Output 1

```text
1 2
0 1
-1 0
2 1
```

### Sample Input 2

```text
4 3
7 7 7 7
7
6
8
```

### Sample Output 2

```text
0 4
1 4
-1 0
```

### Giải thích

Ở ví dụ 1, đoàn $4$ người chọn một trong hai phòng sức chứa $5$, để trống một chỗ. Đoàn $8$ người chọn phòng sức chứa $8$, không còn chỗ trống. Đoàn $11$ người không có phòng phù hợp. Đoàn $1$ người chọn phòng sức chứa $3$, để trống hai chỗ.

Ở ví dụ 2, cả bốn phòng đều có sức chứa $7$. Đoàn $7$ người và đoàn $6$ người đều có bốn lựa chọn tối ưu; đoàn $8$ người không có lựa chọn nào.
