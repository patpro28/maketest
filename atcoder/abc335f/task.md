### Đề bài

Có một hàng gồm $N$ ô vuông được đánh số $1,2,\ldots,N$ và một dãy $A=(A_1,A_2,\ldots,A_N)$.

Ban đầu, ô $1$ được tô màu đen, các ô còn lại có màu trắng; một quân cờ được đặt ở ô $1$.

Bạn được phép lặp đi lặp lại thao tác sau (có thể thực hiện $0$ lần):

- Khi quân cờ đang ở ô $i$, chọn một số nguyên dương $x$, di chuyển quân cờ đến ô $i + A_i \cdot x$ (với điều kiện $i + A_i \cdot x \le N$).  
- Sau khi di chuyển đến ô đó, tô màu đen ô vừa đến.

Hãy đếm số tập hợp các ô có thể được tô màu đen sau khi kết thúc mọi thao tác, modulo $998244353$.

### Dữ liệu vào

- Dòng 1: số nguyên $N$
- Dòng 2: $A_1, A_2, \ldots, A_N$

### Dữ liệu ra

- In ra một số nguyên – số tập hợp các ô có thể được tô màu đen, modulo $998244353$.

### Ràng buộc

- $1 \le N \le 2 \times 10^5$  
- $1 \le A_i \le 2 \times 10^5$

### Sample Input 1
```
5
1 2 3 1 1
```

### Sample Output 1
```
8
```

### Giải thích

Có 8 tập hợp ô được tô đen có thể xuất hiện:

- $\{1\}$
- $\{1,2\}$
- $\{1,2,4\}$
- $\{1,2,4,5\}$
- $\{1,3\}$
- $\{1,4\}$
- $\{1,4,5\}$
- $\{1,5\}$
