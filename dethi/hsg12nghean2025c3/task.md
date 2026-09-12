Nhà Tuấn có một hàng $N$ chậu hoa đơn sắc. Hàng ngày ngắm nhìn hoa, Tuấn thấy rằng nếu đặt các chậu hoa cùng màu về nằm cùng một phía (nửa trái hoặc nữa phải) cửa hàng thì sẽ rất đẹp. Tuấn muốn biết có bao nhiều cách đưa hai chậu hoa bất kì về nằm cùng một phía đề trở thành hàng đẹp.

Dãy màu các chậu hoa được biểu diễn thành một xâu $S$ có độ dài chẵn $N$, mỗi màu là một kí tự latin thường hoặc in hoa, lần lượt được đánh chi số từ $1$ đến $N$. Như vậy xâu $S$ được gọi là xâu đẹp nếu tất cả các kí tự giống nhau của xâu S đều cùng nằm về nửa trái hoặc nửa phải. Ví dụ xâu `abcd`,`AbaB` là các xâu đẹp, còn `aaaa` hay `Bbba` thì không.

Hãy viết chương trình giúp Tuấn giải quyết bài toán trên.

### Yêu cầu

Bạn phải thực hiện $Q$ truy vấn, mỗi truy vấn gồm hai số nguyên dương $x,y$ $(1\le x, y \le N)$. Đưa ra số lượng xâu $T$ thỏa mẫn:

- $T$ là một hoán vị của $S$;
- $T$ là một xâu đẹp;
- Kí tự $S_x$ và $S_y$, phải nằm cùng về một phía (có thể trái hoặc phải) trong xâu $T$.

### Dữ liệu vào

- Dòng đầu gồm xâu $S$ có độ dài $N$ $(N \le 10^5)$;
- Dòng thứ hai gồm một số nguyên dương $Q$ $(Q \le 10^5)$;
- $Q$ dòng tiếp theo, mỗi đòng gồm hai số nguyên dương $x,y$ $(x,y \le N)$.

### Dữ liệu ra

Gồm $Q$ dòng, mỗi dòng trả lời cho mỗi truy vẫn chia lấy dư cho $(10^9+7)$.

### Giới hạn

- $20\%$ số test có $Q=1; 0<N\le 10^3$.
- $80\%$ số test có $1<Q\le 10^5; 0<N\le 10^5$.

### Sample Input

```
Abdb
2
1 3
1 2
```

### Sample Output

```
4
0
```

### Giải thích

Truy vấn $1$, các xâu thỏa mãn là: `Adbb`, `dAbb`, `bbAd`, `bbdA`.
