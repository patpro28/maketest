# BAMTIN — Bám tín hiệu di động

### Đề bài

Một robot hoạt động trên một đường thẳng trong $N$ thời điểm. Ở thời điểm $i$, vùng tín hiệu là đoạn $[L_i,R_i]$. Robot chọn tọa độ nguyên $X_i$ và chịu chi phí

$$\operatorname{dist}(X_i,[L_i,R_i])=\max(L_i-X_i,0)+\max(X_i-R_i,0).$$

Như vậy, nếu robot nằm trong vùng tín hiệu thì không mất chi phí; nếu ở ngoài thì trả khoảng cách tới điểm gần nhất của vùng.

Giữa thời điểm $i$ và $i+1$, robot được đi sang trái tối đa $U_i$ đơn vị hoặc sang phải tối đa $V_i$ đơn vị:

$$-U_i\le X_{i+1}-X_i\le V_i.$$

Tọa độ tại thời điểm đầu được chọn tự do. Không có chi phí di chuyển ngoài các giới hạn trên. Hãy tìm tổng chi phí bám tín hiệu nhỏ nhất trong toàn bộ $N$ thời điểm.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $L_i,R_i$.
- Trong $N-1$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $U_i,V_i$, mô tả khả năng di chuyển từ thời điểm $i$ đến $i+1$. Nếu $N=1$, không có các dòng này.

### Dữ liệu ra

In tổng chi phí nhỏ nhất.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $-10^9\le L_i\le R_i\le10^9$.
- $0\le U_i,V_i\le10^9$.
- Mọi tọa độ robot chọn đều phải là số nguyên.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3
0 0
10 12
0 0
0 3
3 0
```

### Sample Output 1

```text
7
```

### Sample Input 2

```text
2
-2 -1
3 5
0 0
```

### Sample Output 2

```text
4
```

### Sample Input 3

```text
2
-5 -2
4 9
0 20
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, chọn các tọa độ $(0,3,0)$. Robot đi sang phải $3$ đơn vị rồi sang trái $3$ đơn vị. Chỉ thời điểm thứ hai mất chi phí $10-3=7$.

Ở ví dụ 2, robot không được di chuyển. Chọn tọa độ cố định $0$ thì chi phí là $1+3=4$, bằng giá trị nhỏ nhất.

Ở ví dụ 3, chọn $(-2,4)$, vừa nằm trong các vùng tín hiệu, vừa thỏa giới hạn di chuyển. Tổng chi phí bằng $0$.
