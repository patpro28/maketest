# BS13B — Cắt thanh gỗ

### Đề bài

Một xưởng có $N$ thanh gỗ. Thanh thứ $i$ có chiều dài $A_i$ đơn vị. Các thanh gỗ được xem là khác nhau, kể cả khi có cùng chiều dài.

Có $Q$ đơn hàng cần được xem xét. Mỗi đơn hàng được mô tả bởi hai số nguyên $X,K$: cần **đúng một thanh gỗ dài $X$ đơn vị**. Xưởng chọn một thanh gỗ ban đầu, có thể cắt bỏ phần dư để giữ lại một thanh dài đúng $X$. Tổng chiều dài phần bị bỏ đi **không được vượt quá $K$**. Không được ghép nhiều thanh gỗ với nhau.

Với mỗi đơn hàng, hãy đếm số thanh gỗ ban đầu có thể chọn. Thanh có chiều dài đúng bằng $X$ được sử dụng ngay mà không cần cắt.

Các đơn hàng được xét độc lập, dựa trên cùng danh sách $N$ thanh gỗ ban đầu. Việc xét một đơn hàng không làm thay đổi kho gỗ.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, là chiều dài các thanh gỗ. Các số không nhất thiết được sắp xếp.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $X,K$ mô tả một đơn hàng.

### Dữ liệu ra

In $Q$ dòng. Dòng thứ $i$ chứa một số nguyên là số thanh gỗ phù hợp với đơn hàng thứ $i$. Nếu không có lựa chọn nào phù hợp, in $0$.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $1\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le X\le10^9$; $0\le K\le10^9$ trong mỗi truy vấn.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 50% | $N\cdot Q\le10^6$ |
| 2 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 5
8 3 5 5 10
5 3
5 0
9 0
1 1000000000
10 0
```

### Sample Output 1

```text
3
2
0
5
1
```

### Sample Input 2

```text
4 4
7 7 7 7
7 0
8 1
6 1
1000000000 1000000000
```

### Sample Output 2

```text
4
0
4
0
```

### Giải thích

Ở ví dụ 1:

- Đơn hàng 1 cần thanh dài $5$ và cho phép bỏ đi không quá $3$. Hai thanh dài $5$ và thanh dài $8$ đều phù hợp, nên kết quả là $3$. Thanh dài $10$ không phù hợp vì phải bỏ đi $5$.
- Đơn hàng 2 không cho phép bỏ đi phần dư, nên chỉ chọn được hai thanh dài đúng $5$.
- Đơn hàng 3 cần thanh dài đúng $9$ và không cho phép bỏ đi phần dư, nên không có thanh nào phù hợp.
- Đơn hàng 4 cần thanh dài $1$ và cho phép bỏ đi không quá $10^9$, nên cả $5$ thanh đều phù hợp.
- Đơn hàng 5 chỉ chọn được thanh dài đúng $10$, nên kết quả là $1$.

Ở ví dụ 2, cả bốn thanh gỗ đều dài $7$. Đơn hàng 1 và 3 đều có thể chọn bất kỳ thanh nào. Đơn hàng 2 và 4 yêu cầu chiều dài lớn hơn tất cả các thanh trong kho, nên không chọn được thanh nào.
