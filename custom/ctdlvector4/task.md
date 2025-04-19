### Đề bài

Cho một bảng $A$ gồm $N$ hàng và $M$ cột. Mỗi ô của bảng chứa một số nguyên dương. Với mỗi hàng, hãy tính chênh lệch giữa số lớn nhất và số nhỏ nhất trong hàng đó.

### Dữ liệu vào

- Dòng đầu chứa một số nguyên dương $T$ - số lượng bộ test.
- Mỗi bộ test bắt đầu bằng hai số nguyên dương $N$, $M$ - số hàng và số cột của bảng.
- Mỗi dòng trong $N$ dòng tiếp theo chứa $M$ số nguyên dương, là các phần tử của bảng.

### Dữ liệu ra

- Với mỗi bộ test, in ra $N$ số nguyên trên một dòng, số thứ $i$ là chênh lệch giữa số lớn nhất và số nhỏ nhất trong hàng tương ứng.

### Giới hạn

- $1 \leq T \leq 10000$
- $1 \leq N, M \leq 1000$
- Tổng số ô của tất cả các bảng không vượt quá $2\times 10^6$

### Sample Input

```
2
4 3
1 2 3
4 3 2
5 4 9
5 3 1
1 3
1 2 3
```

### Sample Output

```
2 2 5 4
2
```