# Conan

## Đề bài

Minh muốn đọc bộ truyện tranh "Conan" có $10^9$ tập. Ban đầu, anh ấy có $N$ cuốn sách của bộ truyện này. Cuốn sách thứ $i$ có tập $a_i$. Có thể có nhiều cuốn sách cùng một tập.

Minh có thể thực hiện thao tác sau bất kỳ số lần nào (kể cả $0$ lần), nhưng chỉ trước khi bắt đầu đọc:

- Nếu chỉ còn $0$ hoặc $1$ cuốn sách, anh ấy không làm gì.
- Nếu có ít nhất $2$ cuốn sách, anh ấy có thể bán $2$ cuốn sách bất kỳ và mua $1$ cuốn sách của bất kỳ tập nào.

Sau đó, Minh bắt đầu đọc từ tập $1$, tập $2$, tập $3$, ... theo thứ tự. Nếu không có tập tiếp theo cần đọc, anh ấy phải dừng lại ngay lập tức, dù vẫn còn các tập khác.

Hãy tìm tập lớn nhất mà Minh có thể đọc đến. Nếu anh ấy không thể đọc được tập nào, hãy trả về $0$.

## Dữ liệu vào

- Dòng đầu chứa số nguyên $N$ — số cuốn sách ban đầu.
- Dòng thứ hai chứa $N$ số nguyên $a_1, a_2, \ldots, a_N$, mô tả tập của từng cuốn sách.

## Dữ liệu ra

In ra một số nguyên duy nhất là tập cao nhất mà Minh có thể đọc đến.

## Giới hạn

- $1 \leq N \leq 3 \times 10^5$.
- $1 \leq a_i \leq 10^9$.
- Tất cả các giá trị trong dữ liệu vào là số nguyên.

## Ví dụ

### Dữ liệu vào

```text
6
1 2 4 6 7 271
```

### Dữ liệu ra

```text
4
```

### Giải thích

Ban đầu Minh có các tập $\{1, 2, 4, 6, 7, 271\}$. Anh ấy có thể bán cuốn tập $7$ và cuốn tập $271$ để mua tập $3$.

Khi đó, các tập còn lại là $\{1, 2, 4, 6, 3\}$. Minh đọc được liên tiếp từ tập $1$ đến tập $4$. Đây là kết quả lớn nhất có thể đạt được.
