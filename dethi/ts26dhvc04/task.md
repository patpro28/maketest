### Đề bài

Khi ảnh được chụp vào ban đêm, phần lớn bức ảnh sẽ tối và có thể có một số vùng sáng nhỏ được tạo ra bởi các đối tượng phát sáng. Để tìm các vùng sáng nhỏ, người ta thường chuyển ảnh cần xử lý thành một loại ảnh gọi là *ảnh đa mức xám*

Ảnh đa mức xám được biểu diễn bằng một bảng gồm $n$ hàng và $m$ cột, trong đó các hàng được đánh số từ 1 đến $n$, từ trên xuống dưới và các cột được đánh số từ 1 đến $m$, từ trái qua phải. Mỗi ô $(i, j)$ trong bảng chứa một số nguyên thuộc đoạn $[0; 255]$ để biểu diễn mức độ sáng của một điểm ảnh tại hàng $i$ và cột $j$ $(1 \leq i \leq n; 1 \leq j \leq m)$. Giá trị tại ô $(i, j)$ càng lớn thì mức sáng của điểm ảnh càng cao (0: đen; 255: trắng). Một điểm ảnh ở ô $(i, j)$ được gọi là *điểm sáng nổi bật* nếu nó là điểm trung tâm và có giá trị mức sáng lớn nhất trong một bảng con hình vuông có chiều dài cạnh là $2k + 1$, bảng này là một *vùng sáng ảnh*. Một *vùng sáng nổi bật nhất* trong ảnh là một vùng sáng ảnh có tổng giá trị mức sáng của các điểm ảnh lớn nhất so với các vùng sáng khác.

**Yêu cầu**: Viết chương trình tìm một *vùng sáng nổi bật nhất* trong ảnh.

### Dữ liệu vào

- Dòng 1 gồm 3 số nguyên dương $n, m, k$ $(10^2 \leq n, m \leq 5 \times 10^3; 1 \leq k \leq 20)$, mỗi số cách nhau ít nhất một dấu cách.
- Dòng $i + 1$ gồm $m$ số nguyên thuộc đoạn $[0; 255]$, mỗi số cách nhau ít nhất một dấu cách, là giá trị mức sáng của các điểm ảnh trên hàng thứ $i$ của ảnh.

### Dữ liệu ra

- Một dòng chứa tổng giá trị mức sáng của các điểm ảnh trong vùng sáng nổi bật nhất, nếu ảnh không có vùng sáng nổi bật thì ghi số 0.

### Sample Input 1

```
4 5 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
```

### Sample Output 1

```
0
```

### Sample Input 2

```
5 5 1
1 2 1 3 1
1 1 9 1 1
1 2 3 6 4
1 1 5 7 5
2 3 4 6 5
```

### Sample Output 2

```
45
```

### Giải thích

- Test 1: ảnh không có vùng sáng nổi bật.
- Test 2: Có 2 vùng sáng nổi bật với tâm ở $(2, 3)$ và $(4, 4)$ với tổng giá trị mức sáng lần lượt là $28$ và $45$.

### Giới hạn

- $50\%$ số test có $n, m \leq 10^3$ và $1 \le k \le 5$.
- $25\%$ số test có $n, m \leq 3\times 10^3$ và $5 < k \le 10$.
- $25\%$ số test có $n, m \leq 5\times 10^3$ và $10 < k \le 20$.