### Đề bài

Dãy Fibonacci được cho bởi công thức truy hồi như sau:

$$F_n = \begin{cases}
n       & \quad \text{nếu } 0\leq n \leq 1\\
F_{n-1} + F_{n-2} & \quad \text{nếu } n > 1\end{cases}$$

Cho 2 số nguyên $n, k$, tính:

$$S=\sum_{i=1}^{n} F_{i}^k= F_{1}^k + F_{2}^k + \ldots + F_{n}^k$$

Vì kết quả có thể rất lớn, hãy in ra phần dư của kết quả khi chia cho $998244353$.

### Dữ liệu vào

Một dòng duy nhất chứa 2 số nguyên $n, k$.

### Dữ liệu ra

Ghi ra giá trị $S$ tìm được sau khi chia lấy dư cho $998244353$.

### Rằng buộc

- $1 \leq n \leq 10^{18}$
- $1 \leq k \leq 10^6$

### Sample Input 1 

    3 2

### Sample Output 1

    6

### Sample Input 2

    5 1

### Sample Output 2

    12

### Sample Input 3

    1000 1000

### Sample Output 3
    
    954643773
