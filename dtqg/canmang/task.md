# CANMANG — Cân chỉnh mạng cảm biến

### Đề bài

Có $N$ cảm biến được đánh số từ $1$ đến $N$, nối với nhau bằng $N-1$ đường truyền hai chiều tạo thành một cây. Cảm biến $u$ muốn nhận giá trị $A_u$.

Bạn chọn giá trị nguyên $X_u$ cho từng cảm biến, với chi phí hiệu chỉnh $|X_u-A_u|$. Mỗi đường truyền nối $u$ với $v$ có giới hạn $D_{uv}$ và yêu cầu

$$|X_u-X_v|\le D_{uv}.$$

Hãy tìm tổng chi phí hiệu chỉnh nhỏ nhất sao cho mọi đường truyền đều thỏa giới hạn. Không có cảm biến nào được cố định giá trị trước; tọa độ âm được phép.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa ba số nguyên $u,v,D$, mô tả một đường truyền và giới hạn chênh lệch của nó.

### Dữ liệu ra

In tổng chi phí hiệu chỉnh nhỏ nhất.

### Ràng buộc

- $1\le N\le10^5$.
- $-10^9\le A_u\le10^9$.
- $1\le u,v\le N$; $0\le D\le10^9$.
- Các đường truyền tạo thành một cây.
- Mọi $X_u$ đều phải là số nguyên.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3
0 10 0
1 2 2
2 3 2
```

### Sample Output 1

```text
8
```

### Sample Input 2

```text
4
0 2 9 10
1 2 0
1 3 0
3 4 0
```

### Sample Output 2

```text
17
```

### Sample Input 3

```text
3
-5 0 7
1 2 5
2 3 7
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, chọn $(X_1,X_2,X_3)=(0,2,0)$, tổng chi phí bằng $8$ và hai chênh lệch đều bằng $2$.

Ở ví dụ 2, mọi giới hạn đều bằng $0$ nên bốn cảm biến phải nhận cùng giá trị. Chọn giá trị $2$ cho tất cả, tổng chi phí là $2+0+7+8=17$.

Ở ví dụ 3, giữ nguyên các giá trị đã cho; chúng đã thỏa các giới hạn nên chi phí bằng $0$.
