# DPSTR630 — Chèn chữ tạo gương

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Trong một thao tác, bạn chèn một chữ cái thường vào một vị trí bất kỳ, kể cả đầu hoặc cuối xâu. Hãy tìm số thao tác ít nhất để xâu nhận được đối xứng. Không được xóa hoặc thay các ký tự đã có.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số ký tự ít nhất cần chèn.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
4
abca
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
4
race
```

### Sample Output 2

```text
3
```

### Giải thích

Ở ví dụ 1, chèn `b` giữa `c` và chữ `a` cuối để được `abcba`, tốn một thao tác. Ở ví dụ 2, có thể chèn ba chữ `c`, `a`, `r` ở cuối để được `racecar`; không thể dùng ít hơn ba lần chèn.
