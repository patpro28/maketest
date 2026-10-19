# DPTREE22 — Phủ sóng các ngôi làng

### Đề bài

Có $N$ ngôi làng, được đánh số từ $1$ đến $N$. Có $N-1$ con đường hai chiều nối các làng và tạo thành một cây.

Bạn có thể đặt tối đa một trạm phát sóng tại mỗi làng. Chi phí đặt trạm tại làng $i$ là $C_i$. Một trạm chỉ phủ sóng làng đặt trạm và các làng nối trực tiếp với làng đó bằng một con đường; tín hiệu không được truyền tiếp qua các làng khác.

Hãy chọn những làng đặt trạm sao cho mọi làng đều được phủ sóng và tổng chi phí là nhỏ nhất. Một làng có thể được phủ sóng bởi nhiều trạm.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $C_1,C_2,\ldots,C_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một con đường nối hai làng $u$ và $v$.

### Dữ liệu ra

In một số nguyên là tổng chi phí nhỏ nhất để phủ sóng tất cả các làng.

### Ràng buộc

- $1\le N\le 2\cdot 10^5$.
- $1\le C_i\le 10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các con đường tạo thành một cây.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
8 3 20 2 9
1 2
2 3
3 4
4 5
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
1
7
```

### Sample Output 2

```text
7
```

### Giải thích

Ở ví dụ 1, đặt trạm tại làng $2$ và làng $4$, tốn $3+2=5$. Trạm tại làng $2$ phủ các làng $1,2,3$; trạm tại làng $4$ phủ các làng $3,4,5$. Đây là phương án có chi phí nhỏ nhất.

Ở ví dụ 2, chỉ có một làng nên phải đặt trạm tại làng đó.
