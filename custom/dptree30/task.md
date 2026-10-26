# DPTREE30 — Giữ lại các tuyến đường

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$. Mỗi cạnh có một giá trị, có thể âm.

Bạn muốn giữ lại một tập cạnh sao cho **mỗi đỉnh thuộc không quá hai cạnh được giữ lại**. Khi đó các cạnh được giữ tạo thành những đường đi rời nhau; những đỉnh không thuộc cạnh nào được giữ là các đỉnh cô lập và vẫn được phép tồn tại.

Hãy tìm tổng giá trị lớn nhất của các cạnh được giữ lại. Bạn được phép không giữ cạnh nào, khi đó tổng giá trị bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa ba số nguyên $u,v,W$, mô tả một cạnh nối hai đỉnh $u,v$ có giá trị $W$.

### Dữ liệu ra

In một số nguyên là tổng giá trị lớn nhất của một tập cạnh thỏa mãn điều kiện.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le u,v\le N$; $u\ne v$.
- $-10^9\le W\le10^9$.
- Các cạnh tạo thành một cây.

### Sample Input 1

```text
5
1 2 8
1 3 7
1 4 6
1 5 -4
```

### Sample Output 1

```text
15
```

### Sample Input 2

```text
4
1 2 -5
2 3 4
3 4 6
```

### Sample Output 2

```text
10
```

### Giải thích

Ở ví dụ 1, giữ hai cạnh $(1,2)$ và $(1,3)$, có tổng giá trị $8+7=15$. Không thể giữ thêm một cạnh khác vì khi đó đỉnh $1$ thuộc ba cạnh được giữ.

Ở ví dụ 2, giữ hai cạnh $(2,3)$ và $(3,4)$, có tổng giá trị $4+6=10$. Bỏ cạnh giá trị âm giúp tăng tổng giá trị.
