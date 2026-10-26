# DPSTRING01 — Giai điệu nguyên âm

### Đề bài

Cho xâu chữ thường $S$ gồm $N$ ký tự. Ký tự ở vị trí $i$ có điểm thưởng $W_i$.

Bạn chọn một số vị trí theo thứ tự tăng dần để tạo thành một dãy con. Trong dãy con được chọn, hai ký tự liên tiếp phải thuộc hai loại khác nhau: một ký tự là nguyên âm và ký tự còn lại là phụ âm. Các nguyên âm là `a`, `e`, `i`, `o`, `u`; mọi chữ cái thường khác là phụ âm.

Hãy tìm tổng điểm thưởng lớn nhất. Được phép chọn dãy rỗng, có điểm bằng $0$. Điều kiện liên tiếp được xét trong dãy con sau khi chọn, không phải trong xâu ban đầu.

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
aebic
2 9 3 4 5
```

### Sample Output 1

```text
21
```

### Sample Input 2

```text
3
aei
5 2 8
```

### Sample Output 2

```text
8
```

### Giải thích

Ở ví dụ 1, chọn các vị trí $2,3,4,5$ được `ebic`, có tổng điểm $9+3+4+5=21$. Ở ví dụ 2, cả ba ký tự đều là nguyên âm nên chỉ có thể giữ nhiều nhất một ký tự; chọn `i` được $8$ điểm.
