# DTPALCOUNT — Ba loại chuỗi hạt

### Đề bài

Cho xâu $S$ gồm các chữ cái La tinh thường. Có $d$ độ dài phân biệt $L_1,\ldots,L_d$; với độ dài $L_i$, cần chọn đúng $c_i$ đoạn đối xứng.

Mỗi đoạn gồm các ký tự ở những vị trí liên tiếp trong $S$. Các đoạn được chọn đôi một không giao nhau và **không bắt buộc nằm sát nhau**: giữa hai đoạn có thể có các ký tự không được chọn. Được phép bỏ ký tự ở đầu và cuối xâu. Thứ tự các độ dài trên xâu được chọn tùy ý.

Hãy xác định có thể đáp ứng đủ mọi số lượng hay không. Nếu có, in một cách chọn các đoạn theo thứ tự từ trái sang phải. Xâu đối xứng là xâu đọc xuôi và đọc ngược giống nhau.

### Dữ liệu vào

- Dòng đầu chứa xâu $S$.
- Dòng thứ hai chứa số nguyên $d$.
- Trong $d$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $L_i,c_i$.

### Dữ liệu ra

Nếu không thể chọn, in `NO`.

Nếu có thể chọn, dòng đầu in `YES`. Sau đó in đúng $c_1+\cdots+c_d$ dòng, mỗi dòng chứa hai chỉ số $l,r$ của một đoạn, đánh số từ $1$. Các đoạn được in theo thứ tự từ trái sang phải và không giao nhau. Mỗi đoạn phải đối xứng; với mỗi $i$, phải có đúng $c_i$ đoạn dài $L_i$. Nếu có nhiều đáp án, in một đáp án bất kỳ.

### Ràng buộc

- $1\le n=|S|\le100000$.
- $1\le d\le3$.
- $1\le L_i\le100000$; các giá trị $L_i$ đôi một khác nhau.
- $1\le c_i\le20$.
- $S$ chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
bbbbccaa
2
4 1
2 2
```

### Sample Output 1

```text
YES
1 4
5 6
7 8
```

### Sample Input 2

```text
aaaa
2
2 1
3 1
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, chọn `bbbb`, `cc`, `aa`: một đoạn dài $4$ và hai đoạn dài $2$.

Ở ví dụ 2, tổng độ dài cần giữ là $5$, lớn hơn độ dài xâu là $4$.
