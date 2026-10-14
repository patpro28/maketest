# Chọn mặt thẻ

## Đề bài

Có $N$ tấm thẻ, mỗi thẻ có một số nguyên được viết trên cả hai mặt. Mặt trước của thẻ thứ $i$ có số $a_i$, mặt sau có số $b_i$.

Bạn có thể đặt mỗi thẻ với mặt trước hoặc mặt sau hướng lên trên. Hãy xác định xem có thể chọn mặt hướng lên cho mỗi thẻ sao cho tổng các số nhìn thấy bằng $S$ hay không. Nếu có thể, hãy tìm một cách chọn như vậy.

## Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N$ và $S$ — số lượng thẻ và tổng mong muốn.
- $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i$ và $b_i$ tương ứng với hai mặt của thẻ thứ $i$.

## Dữ liệu ra

- Nếu có thể đạt tổng $S$, in `Yes` trên dòng đầu. Dòng thứ hai in một xâu có độ dài $N$, trong đó ký tự thứ $i$ là `A` nếu chọn mặt trước ($a_i$) hoặc `B` nếu chọn mặt sau ($b_i$) của thẻ thứ $i$.
- Nếu không thể đạt tổng $S$, in `No`.

Nếu có nhiều cách chọn hợp lệ, có thể in ra bất kỳ cách nào.

## Giới hạn

- $1 \leq N \leq 100$.
- $1 \leq S \leq 10000$.
- $1 \leq a_i, b_i \leq 100$ với $1 \leq i \leq N$.
- Tất cả các giá trị trong dữ liệu vào là số nguyên.

## Ví dụ 1

### Dữ liệu vào

```text
3 11
1 4
2 3
5 7
```

### Dữ liệu ra

```text
Yes
BAA
```

### Giải thích

Chọn mặt sau của thẻ thứ nhất và mặt trước của hai thẻ còn lại, tổng là $4+2+5=11$.

## Ví dụ 2

### Dữ liệu vào

```text
5 25
2 8
9 3
4 11
5 1
12 6
```

### Dữ liệu ra

```text
No
```
