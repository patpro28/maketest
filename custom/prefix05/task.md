# PREFIX05 — Đoạn lợi nhuận tốt nhất

### Đề bài

Cho lãi hoặc lỗ của một cửa hàng trong $N$ ngày, ngày $i$ có giá trị $A_i$. Giá trị âm biểu thị khoản lỗ.

Hãy chọn một đoạn ngày liên tiếp **không rỗng** sao cho tổng giá trị trên đoạn lớn nhất và in tổng đó. Bạn bắt buộc phải chọn ít nhất một ngày, kể cả khi tất cả các ngày đều lỗ.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là tổng lớn nhất của một đoạn không rỗng.

### Ràng buộc

- $1\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
6
-2 3 -1 4 -5 2
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
3
-5 -2 -7
```

### Sample Output 2

```text
-2
```

### Giải thích

Ở ví dụ 1, chọn các ngày từ $2$ đến $4$ được $3-1+4=6$. Ở ví dụ 2, phải chọn một đoạn không rỗng nên chọn riêng ngày $2$, được $-2$.
