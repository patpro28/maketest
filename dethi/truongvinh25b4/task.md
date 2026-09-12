Công ty ABC đang cung cấp dịch vụ trợ lý AI cho khách hàng. Trong $N$ giây hoạt động, tại giây thứ $i$ công ty ghi nhận khách hàng có mã $a_i$ đang sử dụng dịch vụ.

Để đánh giá mức độ sử dụng dịch vụ, công ty quan tâm đến $Q$ khách hàng có mã số lần lượt là $x_1, x_2,...,x_Q$. Với mỗi khách hàng $x_i$, công ty muốn biết khoảng thời gian ngắn nhất giữa hai lần liên tiếp khách hàng này sử dụng dịch vụ.

Khoảng thời gian được tính bằng hiệu số vị trí giữa hai lần xuất hiện liên tiếp của cùng một mã khách hàng trong dãy. Nếu khách hàng $x_i$ không sử dụng dịch vụ hoặc chỉ xuất hiện duy nhất một lần duy nhất thì kết quả là $0$.

### Dữ liệu vào

- Dòng đầu tiên ghi hai số nguyên $N$ và $Q$.
- Dòng tiếp theo chứa $N$ số nguyên $a_i$.
- $Q$ dòng tiếp theo, mỗi dòng chứa một số nguyên $x_j$.

### Dữ liệu ra

Dòng thứ $i$ chứa một số nguyên duy nhất là khoảng thời gian ngắn nhất giữa hai lần liên tiếp sử dụng dịch vụ của khách hàng có mã $x_i$.

### Rằng buộc

- $1\le N\le 5\times 10^5$.
- $1\le Q\le 10^5$.
- $1\le a_i, x_j\le 10^9$.

### Sample Input

```
6 3
2 1 2 1 4 2
1
2
3
```

### Sample Output

```
2
2
0
```