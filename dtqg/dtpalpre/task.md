# DTPALPRE — Đơn hàng có quan hệ trước sau

### Đề bài

Có $k$ đơn hàng được đánh số từ $1$ đến $k$. Đơn hàng $i$ cần một đoạn đối xứng có độ dài đúng $l_i$ trong xâu $S$.

Cần chọn một đoạn của $S$ cho mỗi đơn hàng. Mỗi đoạn gồm các ký tự ở những vị trí liên tiếp trong $S$. Các đoạn được chọn đôi một không giao nhau và **không bắt buộc nằm sát nhau**: giữa hai đoạn có thể có các ký tự không được chọn. Được phép bỏ ký tự ở đầu và cuối xâu. Xâu đối xứng là xâu đọc xuôi và đọc ngược giống nhau.

Có thêm $e$ yêu cầu $(u,v)$: toàn bộ đoạn của đơn hàng $u$ phải nằm trước đoạn của đơn hàng $v$. Ngoài các yêu cầu này, thứ tự đơn hàng được chọn tùy ý. Hai đơn hàng có cùng độ dài vẫn là hai đơn hàng riêng biệt.

Hãy xác định có tồn tại cách chọn thỏa mãn tất cả điều kiện hay không. Các yêu cầu trước sau có thể mâu thuẫn nhau.

### Dữ liệu vào

- Dòng đầu chứa xâu $S$.
- Dòng thứ hai chứa hai số nguyên $k,e$.
- Dòng thứ ba chứa $k$ số nguyên $l_1,l_2,\ldots,l_k$.
- Trong $e$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một yêu cầu trước sau.

### Dữ liệu ra

In `YES` nếu có cách chọn thỏa mãn; ngược lại in `NO`.

### Ràng buộc

- $1\le n=|S|\le100000$.
- $1\le k\le18$; $0\le e\le k(k-1)$.
- $1\le l_i\le100000$.
- $1\le u,v\le k$ và $u\ne v$ trong mỗi yêu cầu; không có hai yêu cầu giống nhau.
- $S$ chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
aaab
2 1
1 3
2 1
```

### Sample Output 1

```text
YES
```

### Sample Input 2

```text
aaab
2 1
1 3
1 2
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, giao đoạn `aaa` tại các vị trí $1$ đến $3$ cho đơn hàng $2$, rồi giao ký tự `b` tại vị trí $4$ cho đơn hàng $1$.

Ở ví dụ 2, đơn hàng $1$ phải đứng trước đơn hàng $2$. Đoạn đối xứng dài $3$ duy nhất là `aaa` tại các vị trí $1$ đến $3$, nên không còn chỗ cho đoạn dài $1$ đứng trước nó.
