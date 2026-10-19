# DPUPSTAIR03C — Lát hành lang

### Đề bài

Một hành lang gồm $N$ ô liên tiếp, được đánh số từ $1$ đến $N$. Có $K$ ô đã đặt chậu cây. Các ô còn lại cần được lát kín bằng gạch loại dài $1$ ô và loại dài $2$ ô; số viên gạch mỗi loại không giới hạn.

Một viên gạch dài $1$ ô phủ đúng một ô. Một viên gạch dài $2$ ô phủ đúng hai ô liên tiếp. Gạch không được phủ lên ô đặt chậu cây, không được chồng lên nhau và không được vượt ra ngoài hành lang. Mỗi ô không đặt chậu cây phải được phủ đúng một lần.

Hãy đếm số cách lát sử dụng **đúng $M$ viên gạch dài $2$ ô**. Hai cách lát khác nhau nếu tập các cặp ô được phủ bởi gạch dài $2$ ô khác nhau. Nếu tất cả ô đều đặt chậu cây, có đúng một cách không dùng viên gạch nào.

Kết quả cần lấy modulo $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,K,M$.
- Dòng thứ hai chứa $K$ số nguyên phân biệt $b_1,b_2,\ldots,b_K$, là vị trí các ô đặt chậu cây, không nhất thiết được sắp xếp. Nếu $K=0$, dòng này để trống.

### Dữ liệu ra

In số cách lát thỏa mãn yêu cầu, lấy modulo $10^9+7$. Nếu không có cách nào, in $0$.

### Ràng buộc

- $1\le N\le10^5$.
- $0\le K\le N$; $0\le M\le30$.
- $1\le b_i\le N$ với mọi $1\le i\le K$; các $b_i$ đôi một khác nhau.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 30% | $N\le20$ |
| 2 | 20% | $M=0$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
6 1 1
3
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
5 0 2

```

### Sample Output 2

```text
3
```

### Sample Input 3

```text
3 3 0
3 1 2
```

### Sample Output 3

```text
1
```

### Giải thích

Ở ví dụ 1, viên gạch dài $2$ ô có thể phủ một trong ba cặp $(1,2)$, $(4,5)$ hoặc $(5,6)$. Các ô trống còn lại được lát bằng gạch dài $1$ ô.

Ở ví dụ 2, ba cách chọn hai cặp ô là $\{(1,2),(3,4)\}$, $\{(1,2),(4,5)\}$ và $\{(2,3),(4,5)\}$. Ô còn lại được lát bằng một viên gạch dài $1$ ô.

Ở ví dụ 3, mọi ô đều đã đặt chậu cây và $M=0$, nên có đúng một cách không dùng viên gạch nào.
