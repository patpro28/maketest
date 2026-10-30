# PREFIX07 — Ca làm có thời lượng tối thiểu

### Đề bài

Bạn biết giá trị thu được trong từng giờ của một ngày làm việc gồm $N$ giờ. Giờ $i$ có giá trị $A_i$, có thể âm.

Hãy chọn một ca làm gồm ít nhất $K$ giờ liên tiếp sao cho tổng giá trị thu được lớn nhất. In tổng giá trị đó. Bạn bắt buộc phải chọn một ca làm.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là tổng giá trị lớn nhất của một ca làm gồm ít nhất $K$ giờ.

### Ràng buộc

- $1\le N\le200000$.
- $1\le K\le N$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
5 3
4 -5 2 3 -1
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
4 4
-2 1 -3 2
```

### Sample Output 2

```text
-2
```

### Giải thích

Ở ví dụ 1, chọn cả $5$ giờ được tổng $4$, lớn nhất trong các ca có ít nhất $3$ giờ. Ở ví dụ 2, chỉ có thể chọn cả $4$ giờ, được tổng $-2$.
