# DPSTR452 — Đếm các cách chia ít đoạn nhất

### Đề bài

Cho xâu chữ số $S$ và ba số $L,R,B$. Mỗi mảnh hợp lệ phải có độ dài trong $[L,R]$ và tổng các chữ số không vượt quá $B$. Mảnh có thể bắt đầu bằng `0`. Hãy tìm số mảnh ít nhất để phủ toàn bộ xâu bằng các mảnh liên tiếp hợp lệ, đồng thời đếm số cách đạt tối ưu theo vị trí đặt các điểm cắt.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,L,R,B$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ chữ số.

### Dữ liệu ra

In hai số nguyên là số mảnh ít nhất và số cách đạt tối ưu lấy modulo $10^9+7$. Nếu không chia được, in `-1 0`.

### Ràng buộc

- $1\le N\le200000$ và $1\le L\le R\le N$.
- $0\le B\le 9N$.
- $S$ chỉ gồm các chữ số từ `0` đến `9`.

### Sample Input 1

```text
5 1 3 3
11111
```

### Sample Output 1

```text
2 2
```

### Sample Input 2

```text
3 2 3 1
102
```

### Sample Output 2

```text
-1 0
```

### Giải thích

Ở ví dụ 1, hai cách tối ưu có độ dài các mảnh là $(2,3)$ và $(3,2)$. Ở ví dụ 2, chữ `2` đã vượt ngân sách $1$ nên không thể nằm trong mảnh hợp lệ.
