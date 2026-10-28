# DIEUPHOI — Sắp đội hình trên đường thẳng

### Đề bài

Có $N$ xe được đánh số từ $1$ đến $N$, phải đỗ trên một đường thẳng theo đúng thứ tự này. Xe $i$ có chiều dài $L_i$ và muốn đặt đầu xe tại tọa độ nguyên $A_i$.

Bạn chọn tọa độ nguyên $X_i$ cho đầu mỗi xe. Xe $i$ chiếm đoạn từ $X_i$ đến $X_i+L_i$. Giữa xe $i$ và xe $i+1$ phải có khoảng cách ít nhất $G_i$, tức là

$$X_{i+1}\ge X_i+L_i+G_i\qquad(1\le i<N).$$

Được phép đặt xe ở tọa độ âm. Hai đầu đoạn được phép chạm nhau khi khoảng cách an toàn bằng $0$. Chi phí điều chỉnh xe $i$ là $|X_i-A_i|$.

Hãy tìm tổng chi phí nhỏ nhất để bố trí toàn bộ đội xe. Không được thay đổi thứ tự các xe.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,L_i$.
- Nếu $N>1$, dòng cuối chứa $N-1$ số nguyên $G_1,G_2,\ldots,G_{N-1}$. Nếu $N=1$, không có dòng này.

### Dữ liệu ra

In tổng chi phí điều chỉnh nhỏ nhất.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $-10^9\le A_i\le10^9$.
- $1\le L_i\le10^6$.
- $0\le G_i\le10^6$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3
0 2
1 3
8 1
1 0
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
2
10 1
0 1
0
```

### Sample Output 2

```text
11
```

### Sample Input 3

```text
1
-7 100
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, chọn các tọa độ đầu xe $(0,3,8)$. Các điều kiện khoảng cách đều thỏa mãn, tổng chi phí là $0+2+0=2$.

Ở ví dụ 2, chọn $(X_1,X_2)=(0,1)$, tổng chi phí bằng $10+1=11$. Đây là chi phí nhỏ nhất; không được đổi chỗ hai xe.

Ở ví dụ 3, đặt xe tại đúng tọa độ $-7$, không mất chi phí.
