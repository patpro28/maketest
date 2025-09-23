### Đề bài

Có $N$ người được đánh số từ $1$ đến $N$ xếp thành một vòng tròn. Bên phải người thứ nhất là người thứ hai, bên phải người thứ hai là người thứ ba, ..., bên phải người thứ $N$ là người thứ nhất.

Chúng ta sẽ gán cho mỗi người một số tự nhiên bé hơn $M$. Do đó có tất cả $M^N$ cách gán số cho $N$ người.

Hãy đếm số cách gán số sao cho không có hai người đứng kề nhau có cùng số được gán.

### Dữ liệu vào

- Một dòng duy nhất chứa hai số nguyên $N$ và $M$.

### Dữ liệu ra

- In ra kết quả bài toán modulo cho $998244353$.

### Giới hạn

$2 \le M, N \le 10^6$.

### Sample Input 1

    3 3

### Sample Output 1

    6

### Sample Input 2

    4 2

### Sample Output 2

    2

### Giải thích

- Ví dụ 1 có $6$ cách gán số là: $(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)$.
- Ví dụ 2 có $2$ cách gán số là: $(0, 1, 0, 1), (1, 0, 1, 0)$.
