# SEGTREE031 — Chu kỳ đồng bộ

### Đề bài

Có $N$ thiết bị được đánh số từ $1$ đến $N$. Chu kỳ hiện tại của thiết bị $i$ là $A_i$ đơn vị thời gian. Mọi chu kỳ đều là ước dương của $2520$.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: đổi chu kỳ của thiết bị $i$ thành $x$.
- `2 l r`: giả sử các thiết bị từ $l$ đến $r$ bắt đầu cùng lúc tại thời điểm $0$ với các chu kỳ hiện tại. Tìm thời điểm dương nhỏ nhất mà mỗi thiết bị trong đoạn đều vừa hoàn thành một số nguyên chu kỳ.

Mỗi truy vấn là một tình huống độc lập và không làm thời gian hay chu kỳ thay đổi. Tương đương, cần tìm số nguyên dương nhỏ nhất là bội của mọi chu kỳ trong đoạn. Các thao tác được thực hiện theo thứ tự đã cho.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả chu kỳ ban đầu của từng thiết bị.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa thời điểm dương nhỏ nhất thỏa mãn yêu cầu. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i,x\le2520$; $A_i$ và $x$ đều là ước dương của $2520$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 6
4 6 8 9 5
2 1 3
2 4 5
1 2 7
2 1 3
1 1 1
2 1 2
```

### Sample Output 1

```text
24
45
56
7
```

### Sample Input 2

```text
3 5
1 2520 8
2 1 1
2 1 3
1 2 9
2 2 3
2 3 3
```

### Sample Output 2

```text
1
2520
72
8
```

### Giải thích

Ở ví dụ 1, thời điểm dương nhỏ nhất là bội của $4,6,8$ là $24$. Hai chu kỳ $9,5$ cùng hoàn thành một số nguyên chu kỳ lần đầu tại thời điểm $45$. Sau khi đổi chu kỳ thiết bị $2$ thành $7$, ba chu kỳ đầu là $4,7,8$ nên đáp án là $56$. Sau khi đổi chu kỳ thiết bị $1$ thành $1$, đoạn $[1,2]$ có đáp án $7$.

Ở ví dụ 2, đoạn chỉ có chu kỳ $1$ cho đáp án $1$, vì thời điểm $0$ không được tính. Đoạn chứa chu kỳ $2520$ có đáp án $2520$. Sau lần cập nhật, bội chung nhỏ nhất của $9$ và $8$ là $72$.
