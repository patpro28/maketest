# DAYCHUYEN — Dây chuyền sản xuất

### Đề bài

Một nhà máy cần thực hiện $N$ công việc được đánh số từ $1$ đến $N$. Công việc thứ $i$ cần $d_i$ đơn vị thời gian và phải được thực hiện liên tục từ lúc bắt đầu đến lúc hoàn thành.

Nhà máy có đủ máy và nhân lực để thực hiện đồng thời mọi công việc. Thời gian bắt đầu được tính từ mốc $0$. Một công việc không có điều kiện tiên quyết có thể bắt đầu ngay tại thời điểm $0$.

Có $Q$ ràng buộc. Mỗi ràng buộc được mô tả bởi ba số $l_i,r_i,u_i$: công việc $u_i$ chỉ được bắt đầu khi **tất cả** công việc có chỉ số trong đoạn $[l_i,r_i]$ đã hoàn thành. Một công việc có thể chịu nhiều ràng buộc và phải thỏa mãn đồng thời tất cả các ràng buộc đó. Các ràng buộc có thể trùng nhau. Nếu một công việc hoàn thành tại thời điểm $t$, công việc phụ thuộc vào nó được phép bắt đầu ngay tại thời điểm $t$.

Hãy tìm thời điểm sớm nhất có thể hoàn thành toàn bộ công việc. Nếu không có lịch thực hiện hợp lệ do phụ thuộc vòng, hãy thông báo điều đó. Đặc biệt, một công việc bị yêu cầu chờ chính nó thì không thể thực hiện.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $d_1,d_2,\ldots,d_N$, là thời gian thực hiện các công việc.
- Trong $Q$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $l_i,r_i,u_i$, mô tả một ràng buộc.

### Dữ liệu ra

In thời điểm sớm nhất hoàn thành toàn bộ công việc. Nếu không có lịch thực hiện hợp lệ, in $-1$.

### Ràng buộc

- $1\le N\le100000$; $0\le Q\le100000$.
- $1\le d_i\le10^9$.
- $1\le l_i\le r_i\le N$; $1\le u_i\le N$.
- Đáp án có thể vượt phạm vi số nguyên có dấu $32$ bit.

### Sample Input 1

```text
5 3
3 2 4 5 1
1 2 3
2 3 4
1 4 5
```

### Sample Output 1

```text
13
```

### Sample Input 2

```text
3 2
2 3 1
1 1 2
2 2 1
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, công việc $1$ và $2$ bắt đầu tại thời điểm $0$, hoàn thành lần lượt tại thời điểm $3$ và $2$. Công việc $3$ bắt đầu tại thời điểm $3$ và hoàn thành tại thời điểm $7$. Công việc $4$ phải chờ cả công việc $2$ và $3$, nên hoàn thành sớm nhất tại thời điểm $12$. Cuối cùng, công việc $5$ hoàn thành tại thời điểm $13$.

Ở ví dụ 2, công việc $1$ phải chờ công việc $2$, còn công việc $2$ phải chờ công việc $1$. Vì thế không thể hoàn thành toàn bộ công việc.
