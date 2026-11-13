# ICPC0711I — Thu thập kho báu

### Đề bài

Nông dân John phát hiện $N$ kho báu trên đất của mình. Kho báu thứ $i$ ở tọa độ $(x_i,y_i)$ có giá trị $w_i$. Một bức tường của trang trại là đoạn thẳng nối $(0,0)$ và $(X,0)$.

John chỉ có một cọc rào và chỉ có thể đóng cọc tại một vị trí kho báu. Khi đóng cọc tại $P$, ông căng hai đoạn dây nối $P$ với hai đầu bức tường, tạo thành một tam giác. Các kho báu nằm trong tam giác được bảo vệ; kho báu ngay dưới cọc **không được tính**.

Với từng vị trí kho báu theo thứ tự đầu vào, hãy tính tổng giá trị được bảo vệ nếu đặt cọc ở vị trí đó. Dữ liệu bảo đảm không có kho báu khác nằm trên hàng rào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Mỗi dòng trong $N$ dòng tiếp theo chứa ba số nguyên $x_i,y_i,w_i$.

### Dữ liệu ra

In $N$ dòng; dòng thứ $i$ là tổng giá trị kho báu được bảo vệ nếu đặt cọc tại $(x_i,y_i)$.

### Ràng buộc

- $1\le N\le10^5$; $1\le X\le10^9$.
- $-10^9\le x_i\le10^9$; $1\le y_i,w_i\le10^9$.
- Không có hai kho báu trùng tọa độ.
- Với mọi vị trí đặt cọc, không có kho báu khác nằm trên hai đoạn dây hoặc bức tường.

### Sample Input 1

```text
5 8
-8 1 3
-1 10 1
0 3 5
7 1 9
8 2 16
```

### Sample Output 1

```text
0
14
0
0
9
```

### Sample Input 2

```text
6 6
0 1 10
2 3 20
3 1 30
2 5 40
3 5 50
4 5 60
```

### Sample Output 2

```text
0
30
0
50
50
30
```

### Giải thích

Ở ví dụ 1, đặt cọc tại $(-1,10)$ bảo vệ hai kho báu $(0,3)$ và $(7,1)$, có tổng giá trị $5+9=14$. Đặt cọc tại $(8,2)$ chỉ bảo vệ kho báu $(7,1)$, giá trị $9$.

Ở ví dụ 2, đặt cọc tại $(2,5)$ hoặc $(3,5)$ bảo vệ các kho báu $(2,3)$ và $(3,1)$, tổng giá trị $50$.
