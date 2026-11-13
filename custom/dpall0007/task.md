# DPALL0007 — Đoạn không chứa đoạn cấm

### Đề bài

Cho hai dãy $L,R$ cùng có độ dài $N$ và một số nguyên $M$. Đoạn $[L_i,R_i]$ là đoạn cấm thứ $i$.

Đếm số cặp số nguyên $(l,r)$ thỏa mãn $1\le l\le r\le M$ và đoạn $[l,r]$ không chứa trọn bất kỳ đoạn cấm nào. Một đoạn cấm nằm trọn trong $[l,r]$ khi $l\le L_i$ và $R_i\le r$. Các đoạn cấm có thể trùng nhau.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $L_i,R_i$.

### Dữ liệu ra

In số cặp $(l,r)$ thỏa mãn, dưới dạng số nguyên chính xác.

### Ràng buộc

- $1\le N,M\le2\cdot10^5$.
- $1\le L_i\le R_i\le M$.

### Sample Input 1

```text
2 4
1 2
3 4
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
6 20
8 12
14 20
11 13
5 19
4 11
1 6
```

### Sample Output 2

```text
102
```

### Giải thích

- Ví dụ 1. Năm cặp hợp lệ là $(1,1)$, $(2,2)$, $(2,3)$, $(3,3)$ và $(4,4)$.
- Ví dụ 2. Với $r=12$, đầu trái hợp lệ là $9,10,11,12$. Cộng số đầu trái hợp lệ theo từng $r$ cho kết quả $102$.
