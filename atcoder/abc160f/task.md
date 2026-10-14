# ABC160F — Phân phối số nguyên

### Đề bài

Cho một cây gồm $N$ đỉnh được đánh số từ $1$ đến $N$. Cạnh thứ $i$ nối hai đỉnh $a_i$ và $b_i$.

Với mỗi $k=1,2,\ldots,N$, xét cách ghi các số lên các đỉnh của cây như sau:

1. Đầu tiên, ghi số $1$ lên đỉnh $k$.
2. Lần lượt ghi các số $2,3,\ldots,N$. Với mỗi số, chọn một đỉnh chưa được ghi số và kề với ít nhất một đỉnh đã được ghi số, rồi ghi số đang xét lên đỉnh đó. Nếu có nhiều đỉnh thỏa mãn, có thể chọn bất kỳ đỉnh nào trong số đó.

Hãy đếm số cách ghi các số lên các đỉnh có thể thu được với mỗi đỉnh bắt đầu $k$. Hai cách được xem là khác nhau nếu có ít nhất một đỉnh được ghi các số khác nhau.

Vì kết quả có thể rất lớn, hãy in phần dư khi chia cho $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- $N-1$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i$ và $b_i$ mô tả một cạnh của cây.

### Dữ liệu ra

In $N$ dòng. Dòng thứ $k$ chứa số cách ghi các số khi bắt đầu từ đỉnh $k$, lấy modulo $10^9+7$.

### Ràng buộc

- $2 \leq N \leq 2 \times 10^5$.
- $1 \leq a_i,b_i \leq N$.
- Đồ thị được cho là một cây.
- Tất cả các giá trị trong dữ liệu vào là số nguyên.

### Sample Input 1

```text
3
1 2
1 3
```

### Sample Output 1

```text
2
1
1
```

### Sample Input 2

```text
2
1 2
```

### Sample Output 2

```text
1
1
```

### Sample Input 3

```text
5
1 2
2 3
3 4
3 5
```

### Sample Output 3

```text
2
8
12
3
3
```

### Sample Input 4

```text
8
1 2
2 3
3 4
3 5
3 6
6 7
6 8
```

### Sample Output 4

```text
40
280
840
120
120
504
72
72
```

### Giải thích

Ở ví dụ 1, khi bắt đầu từ đỉnh $1$, có hai cách ghi các số lên các đỉnh:

- Các đỉnh $1,2,3$ lần lượt được ghi các số $1,2,3$.
- Các đỉnh $1,2,3$ lần lượt được ghi các số $1,3,2$.
