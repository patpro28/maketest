### Đề bài

Cho dãy số nguyên dương $A$ có $N$ phần tử $a_1,a_2,...,a_N$.

Hãy đếm số cặp số $i,j$ $(1 \leq i < j \leq N)$ thỏa mãn:

$$
\frac{\text{BCNN}(a_i,a_j)}{\text{UCLN}(a_i,a_j)} \text{ là một số chính phương.}
$$

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên dương $N$ $(1 \leq N \leq 10^6)$.
- Dòng thứ hai chứa $N$ số nguyên dương $a_1,a_2,...,a_N$ $(1 \leq a_i \leq 10^6)$.

### Dữ liệu ra

In ra một số nguyên duy nhất là số cặp số $i,j$ thỏa mãn.

### Sample Input

```
5
2 8 3 12 50
```

### Sample Output

```
4
```

### Giải thích

Các cặp số thỏa mãn là $(2, 8), (2, 50), (8, 50), (3, 12)$.

### Subtasks

- **Subtask 1 (20 điểm):** $N \leq 1000$.
- **Subtask 2 (20 điểm):** $a_i$ là các số chính phương.
- **Subtask 3 (30 điểm):** $a_i \leq 1000$.
- **Subtask 4 (30 điểm):** Không có thêm ràng buộc nào.
