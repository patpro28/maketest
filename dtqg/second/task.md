# SECOND — Tổng giá trị lớn thứ hai

### Đề bài

Cho một hoán vị $A_1,A_2,\ldots,A_N$ của các số từ $1$ đến $N$.

Với mỗi đoạn liên tiếp $[l,r]$ có ít nhất hai phần tử, gọi $S(l,r)$ là giá trị lớn thứ hai trong các số $A_l,A_{l+1},\ldots,A_r$. Các phần tử của hoán vị đôi một khác nhau, nên giá trị này luôn được xác định duy nhất.

Hãy tính

$$\sum_{1\le l<r\le N}S(l,r).$$

Nếu $N=1$, không có đoạn hợp lệ và tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In tổng giá trị lớn thứ hai của tất cả các đoạn hợp lệ.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $A$ là hoán vị của các số từ $1$ đến $N$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3
2 1 3
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
2
2 1
```

### Sample Output 2

```text
1
```

### Sample Input 3

```text
4
1 2 3 4
```

### Sample Output 3

```text
14
```

### Giải thích

Ở ví dụ 1, các đoạn $[1,2]$, $[2,3]$, $[1,3]$ có giá trị lớn thứ hai lần lượt là $1,1,2$, tổng bằng $4$.

Ở ví dụ 2, chỉ có một đoạn hợp lệ, với giá trị lớn thứ hai bằng $1$.

Ở ví dụ 3, các đoạn kết thúc tại vị trí $2,3,4$ đóng góp lần lượt $1,4,9$, nên tổng bằng $14$.
