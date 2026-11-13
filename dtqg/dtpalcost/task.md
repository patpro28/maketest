# DTPALCOST — Cắt chuỗi với chi phí nhỏ nhất

### Đề bài

Cho xâu $S$ gồm các chữ cái La tinh thường. Mỗi vị trí $i$ có chi phí giữ lại là $w_i$.

Cần chọn $k$ đoạn của $S$, sao cho chúng đều là xâu đối xứng và có các độ dài $l_1,\ldots,l_k$. Thứ tự các độ dài trên xâu được chọn tùy ý; một độ dài xuất hiện nhiều lần phải được đáp ứng đủ số lần.

Mỗi đoạn gồm các ký tự ở những vị trí liên tiếp trong $S$. Các đoạn được chọn đôi một không giao nhau và **không bắt buộc nằm sát nhau**: giữa hai đoạn có thể có các ký tự không được chọn. Được phép bỏ ký tự ở đầu và cuối xâu.

Chi phí của cách chọn là tổng $w_i$ trên tất cả vị trí thuộc các đoạn được giữ. Ký tự bị bỏ không tính chi phí.

Hãy tìm chi phí nhỏ nhất, hoặc xác định không có cách chọn. Xâu đối xứng là xâu đọc xuôi và đọc ngược giống nhau.

### Dữ liệu vào

- Dòng đầu chứa xâu $S$.
- Dòng thứ hai chứa số nguyên $k$.
- Dòng thứ ba chứa $k$ số nguyên $l_1,\ldots,l_k$.
- Dòng thứ tư chứa $n=|S|$ số nguyên $w_1,\ldots,w_n$.

### Dữ liệu ra

In chi phí nhỏ nhất. Nếu không thể chọn đủ các đoạn, in `-1`.

### Ràng buộc

- $1\le n=|S|\le5000$.
- $1\le k\le10$.
- $1\le l_i\le5000$.
- $0\le w_i\le10^9$.
- $S$ chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
aaaaa
1
2
10 1 1 10 1
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
abba
1
3
1 1 1 1
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, giữ hai ký tự tại vị trí $2,3$ tạo thành `aa`, chi phí bằng $1+1=2$. Đây là chi phí nhỏ nhất.

Ở ví dụ 2, không có đoạn đối xứng dài $3$.
