# KNAPSACK16 — Đội trưởng phải đủ mạnh

### Đề bài

Có $N$ chiến binh. Chiến binh $i$ có sức mạnh $A_i$ và mang trang bị nặng $B_i$.

Bạn chọn một đội là một tập **không rỗng** các chiến binh. Đội hợp lệ nếu tổng trọng lượng trang bị không vượt quá sức mạnh lớn nhất của một thành viên:

$$\sum_{i\in S} B_i\le \max_{i\in S} A_i.$$

Hãy đếm số đội hợp lệ, lấy kết quả theo modulo $998244353$.

Hai đội khác nhau nếu tập chỉ số thành viên khác nhau, kể cả khi các chiến binh có cùng thông số. Nếu nhiều thành viên có sức mạnh lớn nhất bằng nhau, đội vẫn chỉ được tính **một lần**; không tính thêm số cách chọn đội trưởng.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,B_i$.

### Dữ liệu ra

In số đội hợp lệ theo modulo $998244353$.

### Ràng buộc

- $1\le N\le2000$.
- $1\le A_i,B_i\le5000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $A_i\le500$ với mọi $i$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3
3 1
3 2
5 4
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
2
1 2
1 2
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, các đội hợp lệ là $\{1\},\{2\},\{3\},\{1,2\},\{1,3\}$. Đội $\{1,2\}$ chỉ tính một lần dù cả hai chiến binh đều có sức mạnh $3$. Ở ví dụ 2, không chiến binh nào đủ sức gánh trang bị của chính mình.
