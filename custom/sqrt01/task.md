### Đề bài

Cho một bảng chữ nhật gồm $H$ hàng và $W$ cột, mỗi ô có một giá trị $A_{i,j}$. Khoảng cách giữa hai ô $(i_1, j_1)$ và $(i_2, j_2)$ được định nghĩa là $|i_1 - i_2| + |j_1 - j_2|$.

Tìm 2 ô $(i_1, j_1)$ và $(i_2, j_2)$ có cùng giá trị sao cho khoảng cách giữa chúng là nhỏ nhất. Nếu không tồn tại hai ô có cùng giá trị, in $-1$.

### Dữ liệu vào

- Dòng 1: hai số nguyên $H$ và $W$
- Dòng 2 đến dòng $H + 1$: mỗi dòng gồm $W$ số nguyên, biểu diễn giá trị của các ô trong bảng

### Dữ liệu ra

In ra một số nguyên – khoảng cách nhỏ nhất giữa hai ô có cùng giá trị, hoặc $-1$ nếu không tồn tại hai ô như vậy.

### Ràng buộc

- $1 \le H, W \le 500$
- $1 \le A_{i,j} \le 10^6$
- Tất cả các giá trị trong bảng là số nguyên.

### Sample Input 1

```
4 4
1 6 2 1
3 5 7 5
2 4 1 6
1 3 2 4
```

### Sample Output 1

```
2
```

### Giải thích

Khoảng cách nhỏ nhất là giữa hai ô $(2, 2)$ và $(2, 4)$, cả hai đều có giá trị $5$ và khoảng cách giữa chúng là $|2 - 2| + |2 - 4| = 2$.