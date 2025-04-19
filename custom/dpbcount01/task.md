Gần đây, phong trào đếm màu bóng bay đã trở nên phổ biến. Bạn cũng muốn tham gia vào phong trào này. Do đó bạn đã thiết kế một trò chơi liên quan đến đếm màu bóng bay như sau:

Có một dãy bóng bay xếp thành một hàng ngang, đánh số từ $1$ đên $N$. Mỗi bóng bay có một màu sắc, màu sắc được đánh số từ $1$ đên $M$.

Có $Q$ lượt chơi, mỗi lượt bạn sẽ chọn một đoạn liên tiếp $[L, R]$ và yêu cầu người chơi phải đếm số lượng bóng bay của từng màu sắc xuất hiện trong đoạn đó.

Vì tiết kiệm thời gian, bạn chỉ yêu cầu trả lời tích của số lượng bóng bay của từng màu sắc xuất hiện trong đoạn được chọn.

### Dữ liệu vào

- Dòng đầu tiên chứa ba số nguyên $N$, $M$ và $Q$ lần lượt là số lượng bóng bay, số lượng màu sắc và số lượt chơi.
- Dòng thứ hai chứa $N$ số nguyên $a_1, a_2, \ldots, a_N$ lần lượt là màu sắc của các bóng bay.
- $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L$ và $R$ lần lượt là đoạn bạn chọn.

### Dữ liệu ra  

- $Q$ dòng, mỗi dòng chứa một số nguyên là tích của số lượng bóng bay của từng màu sắc trong đoạn được chọn.
- Do kết quả có thể rất lớn, bạn chỉ cần in ra kết quả modulo $10^9 + 7$.

### Ràng buộc

- $1 \leq N, Q \leq 5\times 10^5$
- $1 \leq M \leq 40$
- $1 \leq a_i \leq M$
- $1 \leq L \leq R \leq N$

### Sample Input

```
5 3 2
1 2 3 2 1
1 5
2 4
```

### Sample Output

```
4
2
```

### Giải thích

- Lượt chơi thứ nhất, đoạn được chọn là $[1, 5]$, có $2$ bóng bay màu $1$, $2$ bóng bay màu $2$, $1$ bóng bay màu $3$, tích là $2 \times 2 \times 1 = 4$.
- Lượt chơi thứ hai, đoạn được chọn là $[2, 4]$, có $2$ bóng bay màu $2$, $1$ bóng bay màu $3$, tích là $2 \times 1 = 2$.