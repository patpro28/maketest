### Đề bài

Cho một số nguyên dương $N$. Bạn cần trả lời $Q$ câu hỏi có dạng `T K`. Với $T$ là loại truy vấn và $K$ là một số nguyên dương.

- Nếu $T=1$, bạn phải tìm số lượng số nguyên dương là ước của cả $N$ và $K$.
- Nếu $T=2$, bạn phải tìm số lượng số nguyên dương là ước của $N$ và chia hết cho $K$.
- Nếu $T=3$, bạn phải tìm số lượng số nguyên dương là ước của $N$ và không chia hết cho $K$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên dương $N$ và $Q$.
- $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên dương $T$ và $K$.

### Dữ liệu ra

- Với mỗi truy vấn, in ra kết quả trên một dòng.

### Giới hạn

- $1\le N,K\le 10^{12}$.
- $1\le Q\le 5\times 10^5$.

### Sample Input

```
12 6
1 6
1 14
2 4
2 3
3 12
3 14
```

### Sample Output

```
4
2
2
3
5
6
```

### Giải thích

Tập các số thỏa mãn cho từng truy vấn là:

- $\{1,2,3,6\}$
- $\{1,2\}$
- $\{4,12\}$
- $\{3,6,12\}$
- $\{1,2,3,4,6\}$
- $\{1,2,3,4,6,12\}$
