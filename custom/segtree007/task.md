# SEGTREE007 — Chu kỳ chung của đoạn

### Đề bài

Có $N$ thiết bị được đánh số từ $1$ đến $N$. Thiết bị thứ $i$ có chu kỳ hoạt động là số nguyên dương $A_i$.

Chu kỳ chung của một đoạn $[L,R]$ được định nghĩa là bội chung nhỏ nhất của các số $A_L,A_{L+1},\dots,A_R$. Đây là số nguyên dương nhỏ nhất chia hết cho mọi chu kỳ trong đoạn.

Với mỗi truy vấn $[L,R]$, hãy in chu kỳ chung của đoạn nếu giá trị đó **không vượt quá $10^{18}$**. Nếu giá trị lớn hơn $10^{18}$, in $-1$.

Giá trị đúng bằng $10^{18}$ vẫn được chấp nhận. Các chu kỳ không thay đổi trong suốt $Q$ truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $L,R$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in BCNN của các phần tử trong đoạn nếu không vượt quá $10^{18}$; nếu vượt quá, in $-1$. Mỗi câu trả lời nằm trên một dòng.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le L\le R\le N$.

### Sample Input 1

```text
5 5
4 6 10 3 1
1 3
2 4
4 5
1 1
1 5
```

### Sample Output 1

```text
60
30
3
4
60
```

### Sample Input 2

```text
3 4
999999937 999999929 999999893
1 2
1 3
2 2
3 3
```

### Sample Output 2

```text
999999866000004473
-1
999999929
999999893
```

### Giải thích

Ở ví dụ 1, BCNN của $4,6,10$ là $60$; BCNN của $6,10,3$ là $30$; BCNN của $3,1$ là $3$. Đoạn chỉ có phần tử $4$ trả lời $4$, và BCNN của cả dãy là $60$.

Ở ví dụ 2, hai phần tử đầu có BCNN bằng $999999866000004473$, vẫn nhỏ hơn $10^{18}$. BCNN của cả ba phần tử lớn hơn $10^{18}$ nên truy vấn $[1,3]$ trả lời $-1$. Hai truy vấn một phần tử trả về chính phần tử đó.
