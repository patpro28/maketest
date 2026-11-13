# DPSTR502 — Hoán đổi cặp kề nhau

### Đề bài

Hai xâu $A,B$ có cùng độ dài. Hãy chia các vị trí thành những mảnh liên tiếp có độ dài $1$ hoặc $2$. Với mảnh dài $1$, giữ nguyên hoặc thay chữ nguồn thành chữ đích tương ứng. Với mảnh dài $2$, bắt buộc đổi chỗ hai chữ nguồn và kết quả phải bằng hai chữ đích ở đúng hai vị trí đó. Một lần thay hoặc đổi chỗ tốn một thao tác. Mỗi vị trí thuộc đúng một mảnh. Hãy tìm tổng số thao tác ít nhất.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $N$ ký tự.

### Dữ liệu ra

In tổng số thao tác ít nhất.

### Ràng buộc

- $1\le N\le200000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
4
abcd
badc
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3
abc
baz
```

### Sample Output 2

```text
2
```

### Giải thích

Ví dụ 1 đổi chỗ `ab` và `cd` trong hai mảnh riêng. Ví dụ 2 đổi chỗ hai chữ đầu rồi thay `c` bằng `z`. Một thao tác không đủ để thay đổi cả ba vị trí.
