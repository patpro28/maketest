# KNAPSACK27 — Dàn máy có bộ điều phối đủ mạnh

### Đề bài

Có $N$ mẫu máy. Một máy mẫu $i$ có khả năng điều phối $A_i$ và tải vận hành $B_i$. Mỗi mẫu có số máy không giới hạn.

Bạn chọn một dàn máy không rỗng. Dàn hợp lệ nếu tổng tải vận hành của tất cả máy không vượt khả năng điều phối lớn nhất của một máy trong dàn.

Hãy đếm số dàn hợp lệ modulo $10^9+7$. Một dàn được xác định bởi số máy chọn ở từng mẫu, không phân biệt thứ tự máy. Các mẫu có mã khác nhau được xem là khác nhau dù thông số giống nhau. Không tính thêm số cách chọn một máy làm bộ điều phối.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,B_i$.

### Dữ liệu ra

In số dàn máy hợp lệ modulo $10^9+7$.

### Ràng buộc

- $1\le N\le200$.
- $1\le A_i,B_i\le5000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $A_i\le20$ với mọi $i$ |
| 2 | 30% | $A_i\le500$ với mọi $i$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2
3 1
3 2
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
1
1 2
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, các bộ số lượng là $(1,0),(2,0),(3,0),(0,1),(1,1)$. Tổng tải của chúng không vượt $3$. Ở ví dụ 2, ngay cả một máy cũng có tải lớn hơn khả năng điều phối.
