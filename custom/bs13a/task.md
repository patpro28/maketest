# BS13A — Mua quà

### Đề bài

Một cửa hàng có $N$ món quà. Món quà thứ $i$ có giá $A_i$ đồng. Các món quà được xem là khác nhau, kể cả khi có cùng giá.

Có $Q$ khách hàng cần được tư vấn. Mỗi khách hàng được mô tả bởi hai số nguyên $X,K$: khách mang theo $X$ đồng và muốn mua **đúng một món quà**. Khách đưa toàn bộ $X$ đồng để thanh toán; cửa hàng trả lại phần tiền thừa. Khách chỉ chấp nhận nhận lại **không quá $K$ đồng tiền thừa**, đồng thời không được trả thêm tiền ngoài $X$ đồng đã mang theo.

Với mỗi khách hàng, hãy đếm số món quà có thể chọn mua. Khách được phép không nhận lại tiền thừa nếu giá món quà đúng bằng $X$ đồng.

Các khách hàng được xét độc lập, dựa trên cùng danh sách $N$ món quà ban đầu. Việc xét một khách hàng không làm mất đi món quà nào trong cửa hàng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, là giá của các món quà. Các số không nhất thiết được sắp xếp.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $X,K$ mô tả một khách hàng.

### Dữ liệu ra

In $Q$ dòng. Dòng thứ $i$ chứa một số nguyên là số món quà phù hợp với khách hàng thứ $i$. Nếu không có lựa chọn nào phù hợp, in $0$.

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
8 3
5 0
2 10
10 10
6 1
```

### Sample Output 1

```text
3
2
0
5
2
```

### Sample Input 2

```text
4 4
7 7 7 7
7 0
6 1
8 1
1000000000 0
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

- Khách hàng 1 mang $8$ đồng, chấp nhận tiền thừa không quá $3$ đồng. Hai món giá $5$ đồng và món giá $8$ đồng đều phù hợp, nên kết quả là $3$.
- Khách hàng 2 không chấp nhận tiền thừa, nên chỉ chọn được hai món giá đúng $5$ đồng.
- Khách hàng 3 chỉ mang $2$ đồng, không đủ mua bất kỳ món quà nào.
- Khách hàng 4 có thể mua cả $5$ món quà; tiền thừa khi mua mỗi món đều không quá $10$ đồng.
- Khách hàng 5 mang $6$ đồng và chấp nhận tiền thừa không quá $1$ đồng, nên chọn được hai món giá $5$ đồng.

Ở ví dụ 2, cả bốn món quà đều có giá $7$ đồng. Khách hàng 1 và 3 đều có thể chọn bất kỳ món nào. Khách hàng 2 không đủ tiền; khách hàng 4 không chấp nhận tiền thừa và không có món nào giá đúng $10^9$ đồng.
