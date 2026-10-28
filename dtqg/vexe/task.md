# VEXE — Vé xe theo khu vực

### Đề bài

Có $N$ trạm xe được đánh số từ $1$ đến $N$. Bạn đang ở trạm $S$ và có thể sử dụng $Q$ loại vé.

Loại vé thứ $i$ được mô tả bởi bốn số $u_i,l_i,r_i,c_i$. Khi đang ở trạm $u_i$, bạn có thể trả $c_i$ đồng để đến **một trạm bất kỳ** trong đoạn $[l_i,r_i]$, bao gồm cả hai đầu đoạn. Mỗi lần sử dụng vé chỉ thực hiện một chuyến đi đến trạm đã chọn.

Mỗi loại vé có thể được sử dụng không giới hạn số lần. Các chuyến đi có hướng; không được tự ý đi theo chiều ngược lại. Ngoài những chuyến đi được các loại vé cho phép, không có cách di chuyển nào khác. Các loại vé có thể trùng nhau, và đoạn đích có thể chứa chính trạm xuất phát của vé.

Hãy tính số tiền ít nhất cần trả để đi từ trạm $S$ đến từng trạm. Bạn được phép không đi chuyến nào để ở lại trạm $S$ với chi phí bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,S$.
- Trong $Q$ dòng tiếp theo, dòng thứ $i$ chứa bốn số nguyên $u_i,l_i,r_i,c_i$, mô tả loại vé thứ $i$.

### Dữ liệu ra

In $N$ số nguyên trên một dòng. Số thứ $j$ là chi phí nhỏ nhất để đi từ trạm $S$ đến trạm $j$, hoặc $-1$ nếu không thể đến trạm đó.

### Ràng buộc

- $1\le N\le100000$; $0\le Q\le100000$.
- $1\le S,u_i\le N$.
- $1\le l_i\le r_i\le N$.
- $0\le c_i\le10^9$.
- Đáp án có thể vượt phạm vi số nguyên có dấu $32$ bit.

### Sample Input 1

```text
5 4 1
1 2 3 4
2 4 5 2
3 5 5 1
5 2 2 0
```

### Sample Output 1

```text
0 4 4 6 5
```

### Sample Input 2

```text
4 2 3
3 1 1 0
1 3 3 7
```

### Sample Output 2

```text
0 -1 0 -1
```

### Giải thích

Ở ví dụ 1, từ trạm $1$ có thể đến trạm $2$ hoặc $3$ với chi phí $4$. Đến trạm $4$ qua trạm $2$ tốn $4+2=6$. Đến trạm $5$ qua trạm $3$ chỉ tốn $4+1=5$.

Ở ví dụ 2, bạn bắt đầu tại trạm $3$ và có thể đến trạm $1$ miễn phí. Không có loại vé nào cho phép đến trạm $2$ hoặc $4$.
