# CHONCAY — Chọn đỉnh trên cây động

### Đề bài

Cho một cây có $N$ đỉnh, đánh số từ $1$ tới $N$. Đỉnh $u$ mang trọng số $W_u$, có thể âm.

Một tập đỉnh hợp lệ nếu không có cạnh nào nối hai đỉnh cùng được chọn. Giá trị của tập là tổng trọng số các đỉnh được chọn. Được phép chọn tập rỗng, với giá trị bằng $0$.

Có $Q$ lần cập nhật. Mỗi lần cho hai số $u,x$, yêu cầu gán $W_u=x$. Sau **mỗi lần cập nhật**, hãy tìm giá trị lớn nhất của một tập đỉnh hợp lệ trên toàn bộ cây với các trọng số hiện tại. Hình dạng cây không thay đổi; các cập nhật có hiệu lực tích lũy.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh hai chiều của cây.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,x$, mô tả một lần cập nhật.

### Dữ liệu ra

In $Q$ dòng. Dòng thứ $i$ chứa giá trị lớn nhất sau cập nhật thứ $i$. Không in đáp án trước lần cập nhật đầu tiên.

### Ràng buộc

- $1\le N,Q\le10^5$.
- $-10^9\le W_u,x\le10^9$.
- Mọi chỉ số đỉnh thuộc đoạn $[1,N]$.
- Các cạnh tạo thành một cây.
- Kết quả không vượt $10^{14}$; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3 3
4 5 4
1 2
2 3
2 10
1 20
3 -7
```

### Sample Output 1

```text
10
24
20
```

### Sample Input 2

```text
1 3
7
1 -3
1 0
1 9
```

### Sample Output 2

```text
0
0
9
```

### Sample Input 3

```text
4 3
3 2 2 2
1 2
1 3
1 4
1 10
2 20
1 -5
```

### Sample Output 3

```text
10
24
24
```

### Giải thích

Ở ví dụ 1, sau lần đầu nên chọn riêng đỉnh $2$, đạt $10$. Sau lần thứ hai chọn đỉnh $1,3$, đạt $24$. Sau lần thứ ba chọn riêng đỉnh $1$, đạt $20$.

Ở ví dụ 2, khi trọng số duy nhất không dương có thể chọn tập rỗng; khi trọng số thành $9$, chọn đỉnh đó.

Ở ví dụ 3, sau lần đầu chọn tâm sao, đạt $10$. Sau lần thứ hai chọn cả ba lá, đạt $20+2+2=24$; lần cuối vẫn giữ lựa chọn này.
