<!-- https://www.codechef.com/problems/CTRH -->

### Đề bài

Bạn được cho một **cây** có $N$ đỉnh và $N - 1$ cạnh vô hướng. Bạn phải tô màu từng đỉnh của cây bằng đỏ, xanh dương hoặc xanh lá cây. Mỗi đỉnh phải nhận chính xác một màu, và cuối cùng phải có ít nhất một đỉnh có mỗi màu.

Đối với một đỉnh $u$, định nghĩa **score(u)** là tổng khoảng cách từ $u$ đến các đỉnh gần nhất có hai màu khác. Cụ thể hơn, nếu $u$ được tô màu đỏ, gọi $d_1$ là khoảng cách ngắn nhất từ $u$ đến một đỉnh màu xanh lá cây, và $d_2$ là khoảng cách ngắn nhất từ $u$ đến một đỉnh màu xanh dương. Khi đó, ta có:

$$
\text{score}(u) = d_1 + d_2
$$

Khoảng cách giữa hai đỉnh $u$ và $v$ bằng số cạnh trên đường đi đơn giản giữa $u$ và $v$ trong cây.

**Beauty** của cây được tính là tổng của $\text{score}(u)$ cho tất cả các đỉnh $u$.

Hãy gọi $M$ là **beauty** nhỏ nhất có thể của cây trong tất cả các cách tô màu hợp lệ.

Đếm số cách tô màu hợp lệ đạt được **beauty** $M$. Giá trị này có thể rất lớn, vì vậy hãy trả kết quả theo modulo $10^9 + 7$.

Hai cách tô màu được coi là khác nhau nếu tồn tại ít nhất một đỉnh có màu khác nhau giữa hai cách tô màu.

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên $T$, biểu diễn số bộ test.
- Mỗi bộ test bao gồm nhiều dòng dữ liệu:
  - Dòng đầu tiên của mỗi bộ test chứa một số nguyên $N$ — số đỉnh của cây.
  - $N - 1$ dòng tiếp theo mô tả các cạnh. Dòng thứ $i$ trong các dòng này chứa hai số nguyên $u_i$ và $v_i$, biểu diễn một cạnh vô hướng giữa các đỉnh $u_i$ và $v_i$.

### Dữ liệu ra

Đối với mỗi bộ test, in ra một số nguyên duy nhất: **số cách tô màu hợp lệ** sao cho **beauty** nhỏ nhất của cây có thể đạt được, theo modulo $10^9 + 7$.

### Ràng buộc

- $1 \leq T \leq 10^4$
- $3 \leq N \leq 2 \cdot 10^5$
- $1 \leq u_i, v_i \leq N$
- Tập cạnh mô tả một cây.
- Tổng số đỉnh $N$ trong tất cả các bộ test không vượt quá $2 \cdot 10^5$.

:::samples

:::sample
```input
2
3
1 2
2 3
5
3 4
5 3
2 3
1 2
```

```output
6
18
```

:::

:::


### Giải thích

**Test case 1:** Có 6 cách để có được một cách tô màu hợp lệ, vì chúng ta gán ba màu khác nhau cho ba đỉnh. Tất cả các cách tô màu này đều có **beauty** bằng 8. Do đó, **beauty** nhỏ nhất là 8, và có 6 cách tô màu đạt được giá trị nhỏ nhất này.

**Test case 2:** Một cách tô màu tối ưu là tô đỉnh 3 màu đỏ, đỉnh 2 màu xanh dương, và các đỉnh 1, 4, 5 tất cả màu xanh lá cây. Điểm số của các đỉnh theo cách tô màu này là $[3, 2, 2, 3, 3]$, với **beauty** tổng thể là 13. Có thể chứng minh rằng có 18 cách tô màu hợp lệ khác nhau đạt được **beauty** nhỏ nhất.