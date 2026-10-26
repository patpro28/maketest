# DPTREE24 — Sơn các ngôi làng

### Đề bài

Có $N$ ngôi làng, được đánh số từ $1$ đến $N$. Có $N-1$ con đường hai chiều nối các làng và tạo thành một cây.

Bạn phải sơn mỗi làng bằng đúng một trong hai màu $0$ và $1$. Sơn làng $i$ màu $0$ tốn $A_i$, sơn màu $1$ tốn $B_i$.

Con đường thứ $i$ nối hai làng $u_i,v_i$ và có mức phụ phí $W_i$. Nếu hai làng ở hai đầu con đường mang **hai màu khác nhau**, bạn phải trả thêm $W_i$ cho con đường đó. Nếu hai đầu cùng màu thì không trả phụ phí.

Hãy tìm tổng chi phí nhỏ nhất, bao gồm chi phí sơn tất cả các làng và phụ phí của các con đường.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,B_i$.
- Trong $N-1$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $u_i,v_i,W_i$.

### Dữ liệu ra

In một số nguyên là tổng chi phí nhỏ nhất để sơn tất cả các làng.

### Ràng buộc

- $1\le N\le 2\cdot10^5$.
- $0\le A_i,B_i\le10^9$ với mọi $1\le i\le N$.
- $1\le u_i,v_i\le N$; $u_i\ne v_i$.
- $0\le W_i\le10^9$ với mọi $1\le i<N$.
- Các con đường tạo thành một cây.

### Sample Input 1

```text
3
0 8
9 0
0 7
1 2 2
2 3 3
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
2
0 4
5 0
1 2 100
```

### Sample Output 2

```text
4
```

### Giải thích

Ở ví dụ 1, sơn ba làng lần lượt bằng các màu $0,1,0$. Tổng chi phí sơn bằng $0$, phụ phí của hai con đường bằng $2+3=5$. Đây là tổng chi phí nhỏ nhất.

Ở ví dụ 2, sơn cả hai làng màu $1$, tốn $4+0=4$ và không có phụ phí. Nếu chỉ tối thiểu hóa chi phí sơn tại từng làng riêng lẻ thì hai làng mang màu khác nhau và phải trả phụ phí $100$.
