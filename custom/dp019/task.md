### Đề bài

Cho một mảng $A$ gồm $N$ phần tử được khởi tạo bằng $0$. Bạn cần thực hiện $Q$ truy vấn lên mảng $A$, mỗi truy vấn có dạng:

- `L R X Y`: Bạn cần tăng $A_L$ lên $X$, $A_{L+1}$ lên $X+Y; \ldots;A_R$ lên $X+(R-L)\times Y$.

Sau khi thực hiện xong $Q$ truy vấn, hãy in ra mảng $A$.

### Dữ liệu vào

- Dòng đầu tiên chứa hai số nguyên dương $N, Q$.
- $Q$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên dương $L, R, X, Y$ mô tả một truy vấn.

### Dữ liệu ra

In ra một dòng chứa $N$ số nguyên, là các phần tử của mảng $A$ sau khi thực hiện xong $Q$ truy vấn.

### Giới hạn

- $1 \le N, Q \le 2 \times 10^5$
- $1 \le L \le R \le N$
- $|X|, |Y| \le 10^4$

### Sample Input

```
5 5
2 4 3 1
1 3 4 -2
3 5 2 2
1 5 4 -1
4 5 -2 4
```

### Sample Output

```
8 8 8 8 8
```
