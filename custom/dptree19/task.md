# DPTREE19 — Ngăn dòng nước

### Đề bài

Một hệ thống dẫn nước gồm $N$ điểm, được đánh số từ $1$ đến $N$, và $N-1$ đường ống hai chiều tạo thành một cây. Nước bắt đầu tại điểm $1$ và có thể đi qua mọi đường ống chưa bị cắt.

Một điểm được gọi là **đầu ra** nếu điểm đó khác điểm $1$ và chỉ nối với đúng một đường ống trong hệ thống ban đầu. Đường ống thứ $i$ có chi phí cắt là $W_i$.

Bạn cần cắt một số đường ống sao cho nước từ điểm $1$ không thể đến bất kỳ đầu ra nào. Hãy tìm tổng chi phí cắt nhỏ nhất.

Các đầu ra được xác định theo hệ thống **trước khi cắt**. Một điểm mới trở thành đỉnh bậc một sau khi cắt không được xem là đầu ra mới.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $u_i,v_i,W_i$, mô tả đường ống nối hai điểm $u_i,v_i$ và chi phí cắt đường ống đó.

### Dữ liệu ra

In một số nguyên là tổng chi phí nhỏ nhất để điểm $1$ không còn nối được đến bất kỳ đầu ra nào.

### Ràng buộc

- $2\le N\le 2\cdot 10^5$.
- $1\le u_i,v_i\le N$; $u_i\ne v_i$.
- $1\le W_i\le 10^9$ với mọi $1\le i<N$.
- Các đường ống tạo thành một cây.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
1 2 8
2 3 3
2 4 4
1 5 2
```

### Sample Output 1

```text
9
```

### Sample Input 2

```text
2
1 2 1000000000
```

### Sample Output 2

```text
1000000000
```

### Giải thích

Ở ví dụ 1, các đầu ra là $3,4,5$. Cắt các đường ống $(2,3)$, $(2,4)$ và $(1,5)$ có tổng chi phí $3+4+2=9$. Sau khi cắt, nước có thể đến điểm $2$, nhưng điểm $2$ không phải đầu ra ban đầu.

Ở ví dụ 2, điểm $2$ là đầu ra duy nhất. Bắt buộc phải cắt đường ống nối hai điểm.
