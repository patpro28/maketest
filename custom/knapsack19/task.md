# KNAPSACK19 — Khóa kỹ năng

### Đề bài

Có $N$ kỹ năng được đánh số từ $1$ đến $N$, tạo thành một cây có gốc là kỹ năng $1$. Kỹ năng $1$ không có kỹ năng cha; với $i>1$, kỹ năng cha của $i$ là $P_i$ và $1\le P_i<i$.

Học kỹ năng $i$ tốn $C_i$ điểm kỹ năng và tăng thêm $V_i$ sức mạnh. Mỗi kỹ năng chỉ được học một lần. Muốn học một kỹ năng khác gốc, bạn phải học kỹ năng cha của nó trước; vì vậy phải học cả các tổ tiên của nó.

Bạn có $W$ điểm kỹ năng. Hãy tìm tổng sức mạnh tăng thêm lớn nhất có thể đạt được, với tổng chi phí không vượt $W$. Bạn được phép không học kỹ năng nào, khi đó chi phí và sức mạnh tăng thêm đều bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,W$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $P_i,C_i,V_i$.
- $P_1=0$; với $i>1$, $1\le P_i<i$.

### Dữ liệu ra

In tổng sức mạnh tăng thêm lớn nhất.

### Ràng buộc

- $1\le N\le200$; $0\le W\le500$.
- $1\le C_i\le500$; $1\le V_i\le10^9$.
- $P_1=0$; $1\le P_i<i$ với mọi $2\le i\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $P_i=i-1$ với mọi $i>1$ (cây là một đường đi) |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4 5
0 2 3
1 2 6
1 3 10
2 1 5
```

### Sample Output 1

```text
14
```

### Sample Input 2

```text
2 1
0 2 1
1 1 100
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, học các kỹ năng $1,2,4$ theo thứ tự, tốn $2+2+1=5$ điểm và tăng $3+6+5=14$ sức mạnh. Ở ví dụ 2, không đủ điểm học kỹ năng gốc nên cũng không thể học kỹ năng thứ hai.
