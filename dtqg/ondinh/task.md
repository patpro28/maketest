# ONDINH — Hiệu chỉnh tín hiệu có quán tính

### Đề bài

Có $N$ giá trị đo $A_1,A_2,\ldots,A_N$. Bạn cần chọn các giá trị nguyên $X_1,X_2,\ldots,X_N$ để hiệu chỉnh tín hiệu.

Giá trị đo thứ $i$ có độ tin cậy $W_i$. Nếu hiệu chỉnh nó thành $X_i$, bạn trả chi phí $W_i|X_i-A_i|$. Ngoài ra, giữa hai vị trí liên tiếp $i$ và $i+1$, bạn trả thêm $C_i|X_{i+1}-X_i|$ để hạn chế sự thay đổi đột ngột.

Tổng chi phí là

$$\sum_{i=1}^{N}W_i|X_i-A_i|+\sum_{i=1}^{N-1}C_i|X_{i+1}-X_i|.$$

Không có điều kiện bắt buộc các giá trị hiệu chỉnh phải tăng, giảm hoặc giữ nguyên. Hãy tìm tổng chi phí nhỏ nhất.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,W_i$.
- Nếu $N>1$, dòng cuối chứa $N-1$ số nguyên $C_1,C_2,\ldots,C_{N-1}$. Nếu $N=1$, không có dòng này.

### Dữ liệu ra

In tổng chi phí nhỏ nhất.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $0\le A_i\le10^6$.
- $1\le W_i\le10^6$.
- $1\le C_i\le10^6$.
- Mọi $X_i$ đều phải là số nguyên.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3
0 5
10 5
0 5
1 1
```

### Sample Output 1

```text
20
```

### Sample Input 2

```text
3
0 1
10 1
0 1
100 100
```

### Sample Output 2

```text
10
```

### Sample Input 3

```text
1
17 1000000
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, giữ nguyên các giá trị $(0,10,0)$. Không mất chi phí hiệu chỉnh, còn chi phí thay đổi giữa hai vị trí là $10+10=20$.

Ở ví dụ 2, chọn $(0,0,0)$. Chỉ giá trị đo thứ hai bị thay đổi, với chi phí $10$; không còn chi phí giữa các vị trí.

Ở ví dụ 3, chọn $X_1=17$, chi phí bằng $0$.
