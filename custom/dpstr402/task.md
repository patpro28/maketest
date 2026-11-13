# DPSTR402 — Ít đoạn số nhất

### Đề bài

Cho xâu chữ số $S$ và đoạn giá trị $[L,R]$. Hãy chia toàn bộ xâu thành ít đoạn liên tiếp không rỗng nhất, sao cho mỗi đoạn biểu diễn một số trong $[L,R]$ và không có chữ số $0$ đứng đầu.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,L,R$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ chữ số.

### Dữ liệu ra

In số đoạn ít nhất. In $-1$ nếu không có cách chia.

### Ràng buộc

- $1\le N\le200000$.
- $1\le L\le R\le10^9$.
- $S$ chỉ gồm các chữ số từ `0` đến `9`.

### Sample Input 1

```text
3 1 21
210
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 20 99
123
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, cách tối ưu là `2 | 10`. Lấy `21` trước sẽ để lại `0`. Ở ví dụ 2, không có tiền tố nào biểu diễn số trong đoạn yêu cầu.
