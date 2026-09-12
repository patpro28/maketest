### Đề bài

Trang trại của Farmer John gồm $N$ đồng cỏ được đánh số từ $1$ đến $N$, nối với nhau bằng $N-1$ con đường hai chiều tạo thành một cây. Chuồng bò nằm tại đồng cỏ số $1$, và từ chuồng có thể đi đến mọi đồng cỏ.

Buổi sáng, mỗi con bò đứng tại đồng cỏ của mình, nhưng đến khi Farmer John quay lại thì không biết chúng chạy đi đâu. Ông chỉ biết rằng:

* Bò **luôn chạy ra xa chuồng** (nghĩa là khi di chuyển, chúng chỉ được đi đến đồng cỏ có khoảng cách tới chuồng lớn hơn).
* Mỗi con bò **không chạy quá quãng đường dài hơn $L$**.

Với mỗi đồng cỏ $i$, hãy tính xem nếu con bò bắt đầu tại $i$, thì nó có thể kết thúc ở bao nhiêu đồng cỏ khác nhau (tính cả chính đồng cỏ đó).

### Dữ liệu vào

* Dòng 1: hai số nguyên $N$ và $L$.
* Các dòng $2..N$: dòng thứ $i$ chứa hai số $p_i$ và $l_i$, trong đó:

    * $p_i$ ($1 \le p_i < i$) là đồng cỏ đầu tiên trên đường đi ngắn nhất từ $i$ về chuồng.
    * $l_i$ ($1 \le l_i \le 10^{12}$) là độ dài đoạn đường giữa $i$ và $p_i$.

### Dữ liệu ra

* In ra $N$ dòng, dòng thứ $i$ chứa số lượng đồng cỏ mà bò từ đồng cỏ $i$ có thể chạy đến (bao gồm chính đồng cỏ đó), sao cho:

    * đường đi luôn hướng ra xa chuồng,
    * tổng độ dài đường đi $\le L$.

### Ràng buộc

* $1 \le N \le 200,000$
* $1 \le L \le 10^{18}$
* $1 \le p_i < i$
* $1 \le l_i \le 10^{12}$
* Cần dùng biến kiểu 64-bit.

### Sample Input 1

    4 5
    1 4
    2 3
    1 5

### Sample Output 1

    3
    2
    1
    1

### Giải thích

* Từ đồng cỏ $1$, bò có thể ở các đồng cỏ ${1, 2, 4}$.
* Từ đồng cỏ $2$, bò có thể ở ${2, 3}$.
* Các đồng cỏ $3$ và $4$ nằm xa nhất, nên bò đứng ở đó chỉ có thể ở lại đúng vị trí của mình.

