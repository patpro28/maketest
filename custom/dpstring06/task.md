# DPSTRING06 — Nhịp đọc dễ nhớ

### Đề bài

Cho xâu chữ thường $S$ gồm $N$ ký tự. Giữ ký tự ở vị trí $i$ được $W_i$ điểm.

Bạn chọn một dãy con sao cho không có hai nguyên âm liên tiếp và không có ba phụ âm liên tiếp trong dãy được chọn. Các nguyên âm là `a`, `e`, `i`, `o`, `u`; mọi chữ cái thường khác là phụ âm. Điều kiện liên tiếp được xét sau khi bỏ các vị trí không chọn.

Hãy tìm tổng điểm lớn nhất. Được phép chọn dãy rỗng với điểm bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- $S$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
5
aabbb
8 2 5 1 7
```

### Sample Output 1

```text
20
```

### Sample Input 2

```text
5
abaca
1 2 3 4 5
```

### Sample Output 2

```text
15
```

### Giải thích

Ở ví dụ 1, chọn các vị trí $1,3,5$ được `abb`, có điểm $8+5+7=20$. Trong hai chữ `a` chỉ giữ được nhiều nhất một; trong ba chữ `b` chỉ giữ được nhiều nhất hai. Ở ví dụ 2, giữ cả xâu được $1+2+3+4+5=15$ điểm.
