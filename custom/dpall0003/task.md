# DPALL0003 — Cầu thang đổi nhịp

### Đề bài

Một cầu thang có $N$ bậc đánh số từ $1$ đến $N$. Bạn bắt đầu ở vị trí $0$. Mỗi lần nhảy lên đúng $1$, $2$ hoặc $3$ bậc, không vượt quá bậc $N$. Hai cú nhảy liên tiếp phải có độ dài khác nhau.

Khi đáp xuống bậc $i$, bạn trả phí $A_i$. Hãy tìm tổng phí nhỏ nhất để đến bậc $N$ và đếm số lộ trình đạt tổng phí đó. Hai lộ trình khác nhau nếu dãy độ dài các cú nhảy khác nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In hai số nguyên là tổng phí nhỏ nhất và số lộ trình đạt tổng phí đó modulo $10^9+7$.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $0\le A_i\le10^9$.

### Sample Input 1

```text
4
0 0 0 0
```

### Sample Output 1

```text
0 3
```

### Sample Input 2

```text
5
8 2 10 3 1
```

### Sample Output 2

```text
3 1
```

### Giải thích

- Ví dụ 1. Ba dãy độ dài cú nhảy là $(1,3)$, $(3,1)$ và $(1,2,1)$. Cả ba có phí bằng $0$.
- Ví dụ 2. Nhảy lần lượt $2$ và $3$ bậc để đáp xuống bậc $2$ rồi bậc $5$, với tổng phí $2+1=3$. Đây là lộ trình duy nhất có tổng phí $3$.
