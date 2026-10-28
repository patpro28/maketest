# CHIACHUYEN — Chia chuyến hàng

### Đề bài

Có $N$ kiện hàng xếp thành một dãy theo thứ tự từ $1$ đến $N$. Kiện thứ $i$ có chỉ số bảo quản $H_i$.

Bạn phải vận chuyển toàn bộ dãy bằng cách chia dãy thành các đoạn liên tiếp không rỗng. Mỗi kiện thuộc đúng một đoạn; mỗi đoạn được vận chuyển trong một chuyến. Không được thay đổi thứ tự các kiện.

Mỗi chuyến phải chứa ít nhất $L$ và nhiều nhất $R$ kiện. Nếu một chuyến chở các kiện từ $l$ đến $r$, chi phí của chuyến đó là

$$C+\max_{l\le i\le r} H_i-\min_{l\le i\le r} H_i,$$

trong đó $C$ là phí cố định để mở một chuyến, giống nhau cho mọi chuyến.

Hãy tìm tổng chi phí nhỏ nhất để vận chuyển toàn bộ dãy, hoặc xác định rằng không thể chia thành các chuyến hợp lệ.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,L,R,C$.
- Dòng thứ hai chứa $N$ số nguyên $H_1,H_2,\ldots,H_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất. Nếu không có cách chia hợp lệ, in $-1$.

### Ràng buộc

- $1\le N\le 2\cdot10^5$.
- $1\le L\le R\le N$.
- $0\le C\le 10^9$.
- $1\le H_i\le 10^9$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
6 2 3 4
1 2 10 11 3 4
```

### Sample Output 1

```text
15
```

### Sample Input 2

```text
5 3 3 7
2 8 1 4 9
```

### Sample Output 2

```text
-1
```

### Sample Input 3

```text
4 1 4 0
1 1000000000 1 1000000000
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, chia thành ba chuyến $[1,2]$, $[3,4]$, $[5,6]$. Mỗi chuyến có chi phí $4+1=5$, tổng bằng $15$. Nếu chỉ dùng hai chuyến thì buộc chia thành $[1,3]$ và $[4,6]$, có tổng chi phí $13+12=25$.

Ở ví dụ 2, mỗi chuyến phải có đúng $3$ kiện, nên không thể vận chuyển toàn bộ $5$ kiện.

Ở ví dụ 3, chở mỗi kiện bằng một chuyến riêng thì mọi chuyến đều có chi phí $0$.
