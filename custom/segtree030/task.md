# SEGTREE030 — Chia các bao kẹo

### Đề bài

Có $N$ bao kẹo được đánh số từ $1$ đến $N$. Ban đầu, bao $i$ chứa $A_i$ viên kẹo.

Để chia kẹo trên đoạn $[l,r]$, bạn chọn một số nguyên dương $d$ và chia **từng bao riêng biệt** thành các gói, mỗi gói có đúng $d$ viên. Phải dùng hết kẹo trong từng bao, không được chuyển kẹo giữa các bao.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: thay số kẹo trong bao $i$ bằng $x$.
- `2 l r`: tìm số viên kẹo $d$ lớn nhất có thể có trong mỗi gói khi chia các bao từ $l$ đến $r$ theo cách trên.

Truy vấn chỉ yêu cầu tính đáp án, không làm thay đổi số kẹo trong các bao. Mỗi truy vấn sử dụng số kẹo sau tất cả thao tác cập nhật trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả số viên kẹo ban đầu trong từng bao.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa số viên kẹo lớn nhất có thể có trong mỗi gói. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 6
12 18 24 7 21
2 1 3
2 4 5
1 2 30
2 1 3
1 1 25
2 1 2
```

### Sample Output 1

```text
6
7
6
5
```

### Sample Input 2

```text
2 4
1 1000000000
2 1 2
2 2 2
1 1 1000000000
2 1 2
```

### Sample Output 2

```text
1
1000000000
1000000000
```

### Giải thích

Ở ví dụ 1, ba bao đầu có $12,18,24$ viên. Mỗi gói chứa $6$ viên thì từng bao đều chia hết, và không có số lớn hơn $6$ cùng chia hết cả ba số. Hai bao cuối cùng chia được thành các gói $7$ viên. Sau khi sửa bao $2$ thành $30$, đáp án trên ba bao đầu vẫn là $6$. Sau khi sửa bao $1$ thành $25$, hai bao đầu có thể chia thành các gói tối đa $5$ viên.

Ở ví dụ 2, khi đoạn có bao chỉ chứa $1$ viên thì mỗi gói chỉ có thể chứa $1$ viên. Đoạn chỉ gồm bao thứ hai có thể chia thành một gói chứa toàn bộ $10^9$ viên của bao đó.
