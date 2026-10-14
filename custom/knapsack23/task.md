# KNAPSACK23 — Xưởng robot hàng loạt

### Đề bài

Tạo một robot mới có sức mạnh $1$ tốn một đơn vị năng lượng. Sau đó mỗi lần nâng cấp tốn một đơn vị năng lượng: chọn số nguyên $x>0$ và thay sức mạnh hiện tại $u$ bằng

$$u+\left\lfloor\frac{u}{x}\right\rfloor.$$

Có $N$ mẫu robot. Một robot có sức mạnh **đúng bằng** $B_i$ có thể được bán theo mẫu $i$ với giá $V_i$. Bạn được sản xuất không giới hạn robot theo mỗi mẫu; một robot chỉ được bán một lần theo một mẫu. Các mẫu có cùng sức mạnh yêu cầu vẫn có thể có giá bán khác nhau.

Với tối đa $K$ năng lượng, hãy tìm tổng tiền bán robot lớn nhất. Bạn được phép không sản xuất robot nào. Chi phí tạo khung phải trả riêng cho từng robot, kể cả mẫu có $B_i=1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $B_i,V_i$.

### Dữ liệu ra

In tổng tiền bán robot lớn nhất.

### Ràng buộc

- $1\le N\le100$; $0\le K\le20000$.
- $1\le B_i\le1000$; $1\le V_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $K\le20$, $B_i\le20$ |
| 2 | 30% | $B_i\le100$ với mọi $i$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 4
1 3
2 7
```

### Sample Output 1

```text
14
```

### Sample Input 2

```text
1 0
1 10
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, mỗi robot mẫu thứ hai cần một năng lượng tạo khung và một lần nâng cấp $1\to2$. Sản xuất hai robot tốn $4$ năng lượng và bán được $14$. Ở ví dụ 2, không đủ năng lượng tạo khung.
