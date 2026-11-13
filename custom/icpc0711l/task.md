# ICPC0711L — Thao tác trên dữ liệu dạng cây

### Đề bài

Cho cây có $n$ đỉnh, đánh số từ $1$ đến $n$, gốc tại đỉnh $1$. Mỗi cạnh có trọng số nguyên dương. Ban đầu, mỗi đỉnh có màu đen hoặc trắng.

Thực hiện lần lượt $q$ thao tác:

- `1 u`: đổi màu đỉnh $u$ (đen thành trắng, trắng thành đen).
- `2 u`: xét các đỉnh đen trong cây con gốc $u$. Lập đồ thị vô hướng đầy đủ trên các đỉnh này; trọng số cạnh bằng khoảng cách trên cây, tức tổng trọng số cạnh trên đường đi đơn giữa hai đỉnh. Tìm độ dài nhỏ nhất của một chu trình xuất phát ở một đỉnh, thăm mỗi đỉnh còn lại đúng một lần rồi quay về điểm xuất phát.
- `3 u`: lập cùng đồ thị như thao tác loại $2$, rồi tìm độ dài nhỏ nhất của một đường đi xuất phát ở một đỉnh bất kỳ và thăm mỗi đỉnh còn lại đúng một lần, không cần quay lại điểm đầu.

Nếu chỉ có một đỉnh đen, cả hai kết quả đều bằng $0$. Với hai đỉnh đen, chu trình đi từ đỉnh này sang đỉnh kia rồi quay lại.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $n$.
- Dòng thứ hai chứa xâu nhị phân độ dài $n$; ký tự thứ $i$ bằng `1` nếu đỉnh $i$ màu đen, bằng `0` nếu màu trắng.
- Mỗi dòng trong $n-1$ dòng tiếp theo chứa ba số nguyên $u,v,c$, mô tả một cạnh trọng số $c$.
- Dòng tiếp theo chứa số nguyên $q$.
- Mỗi dòng trong $q$ dòng tiếp theo chứa hai số nguyên $t,u$, mô tả một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại $2$ hoặc $3$, in độ dài nhỏ nhất cần tìm trên một dòng.

### Ràng buộc

- $2\le n,q\le2\cdot10^5$.
- $1\le u,v\le n$; $1\le c\le10^9$.
- Các cạnh tạo thành một cây.
- $t\in\{1,2,3\}$.
- Với mỗi thao tác loại $2$ hoặc $3$, cây con được hỏi chứa ít nhất một đỉnh đen.

### Sample Input 1

```text
6
001110
1 2 1
1 4 2
4 6 3
2 5 2
2 3 4
9
2 1
1 4
2 1
1 6
2 1
2 2
1 4
2 2
2 5
```

### Sample Output 1

```text
18
12
24
12
12
0
```

### Sample Input 2

```text
6
001110
1 2 1
1 4 2
4 6 3
2 5 2
2 3 4
9
3 1
1 4
3 1
1 6
3 1
3 2
1 4
3 2
3 5
```

### Sample Output 2

```text
11
6
14
6
6
0
```

### Giải thích

Ban đầu các đỉnh đen là $3,4,5$. Khoảng cách giữa chúng lần lượt là $d(3,4)=7$, $d(4,5)=5$, $d(5,3)=6$. Vì vậy truy vấn đầu của ví dụ 1 có chu trình ngắn nhất dài $7+5+6=18$; truy vấn đầu của ví dụ 2 có đường đi ngắn nhất dài $6+5=11$.

Ở truy vấn cuối của cả hai ví dụ, cây con gốc $5$ chỉ có một đỉnh đen, nên kết quả bằng $0$.
