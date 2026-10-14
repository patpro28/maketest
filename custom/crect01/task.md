# Đếm hình chữ nhật

## Đề bài

Cho một bảng kích thước $M\times N$, được chia thành lưới ô vuông đơn vị gồm $M$ dòng và $N$ cột. Trên mỗi ô của bảng ghi số $0$ hoặc $1$.

Các dòng được đánh số từ $1$ đến $M$ theo thứ tự từ trên xuống dưới. Các cột được đánh số từ $1$ đến $N$ theo thứ tự từ trái sang phải.

Hãy đếm số hình chữ nhật gồm các ô của bảng thỏa mãn cả hai điều kiện:

- Chỉ gồm các ô ghi số $1$.
- Các cạnh song song với cạnh bảng.

Mỗi hình chữ nhật được xác định bởi một đoạn dòng liên tiếp và một đoạn cột liên tiếp, đều không rỗng. Hai hình chữ nhật khác nhau nếu phạm vi dòng hoặc phạm vi cột của chúng khác nhau. Hình chữ nhật có thể chỉ gồm một ô.

## Dữ liệu vào

- Dòng đầu ghi hai số nguyên $M,N$.
- Trong $M$ dòng tiếp theo, dòng thứ $i$ ghi $N$ số nguyên, số thứ $j$ là giá trị trên ô $(i,j)$ của bảng.

## Dữ liệu ra

In ra một số nguyên duy nhất là số lượng hình chữ nhật thỏa mãn yêu cầu.

## Ràng buộc

- $1\leq M,N\leq 1000$.
- Mỗi ô có giá trị $0$ hoặc $1$.

## Ví dụ

### Dữ liệu vào

```text
11 13
0 0 0 0 0 1 0 0 0 0 0 0 0
0 0 0 0 1 1 1 0 0 0 0 0 0
0 0 1 1 1 1 1 1 1 0 0 0 0
0 0 1 1 1 1 1 1 1 0 0 0 0
0 1 1 1 1 1 1 1 1 1 0 0 0
1 1 1 1 1 1 1 1 1 1 1 0 0
0 1 1 1 1 1 1 1 1 1 0 0 0
0 0 1 1 1 1 1 1 1 0 0 0 0
0 0 1 1 1 1 1 1 1 0 0 0 0
0 0 0 0 1 1 1 0 0 0 0 1 1
0 0 0 0 0 1 0 0 0 0 0 1 1
```

### Dữ liệu ra

```text
1039
```
