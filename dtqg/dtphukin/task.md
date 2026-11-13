# DTPHUKIN — Phủ kín bằng số 1

### Đề bài

Cho một mảng nhị phân $B$ gồm $M$ phần tử. Trong mỗi phép biến đổi, chọn một đoạn $[L,R]$ với $1\le L\le R\le M$ sao cho trong đoạn đó có nhiều số $1$ hơn số $0$. Sau đó, đặt tất cả phần tử trong đoạn bằng $1$.

Ta gọi $B$ là **phủ kín được** nếu có thể biến $B$ thành mảng toàn số $1$ bằng một số hữu hạn phép biến đổi. Nếu $B$ đã toàn số $1$ thì có thể dùng $0$ phép biến đổi.

Cho mảng nhị phân $A$ gồm $N$ phần tử. Hãy đếm số cặp chỉ số $(l,r)$ với $1\le l\le r\le N$ sao cho đoạn con $A[l,r]$ phủ kín được. Khi xét một đoạn con, mọi phép biến đổi chỉ được thực hiện trên các phần tử thuộc đoạn đó.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $T$ là số bộ test.
- Mỗi bộ test gồm hai dòng.
  - Dòng thứ nhất chứa số nguyên $N$.
  - Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$ cách nhau bởi dấu cách.

### Dữ liệu ra

Với mỗi bộ test, in trên một dòng số lượng đoạn con phủ kín được của $A$.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- $A_i\in\{0,1\}$ với mọi $1\le i\le N$.
- Tổng $N$ qua tất cả bộ test không vượt quá $2\cdot 10^5$.

### Sample Input 1

```text
3
3
1 0 1
4
0 1 0 0
3
1 1 1
```

### Sample Output 1

```text
3
1
6
```

### Sample Input 2

```text
3
4
1 0 0 1
5
1 0 1 0 0
4
0 1 1 0
```

### Sample Output 2

```text
2
5
6
```

### Giải thích

- Ví dụ 1. Với $A=[1,0,1]$, hai đoạn một phần tử chứa $1$ và đoạn $[1,3]$ đều phủ kín được. Với $A=[0,1,0,0]$, chỉ đoạn $[2,2]$ phủ kín được. Với $A=[1,1,1]$, cả sáu đoạn con đều đã toàn số $1$.
- Ví dụ 2. Với $A=[1,0,0,1]$, chỉ hai đoạn một phần tử chứa $1$ phủ kín được. Với $A=[1,0,1,0,0]$, ngoài hai đoạn một phần tử, các đoạn $[1,3]$, $[1,4]$ và $[1,5]$ đều phủ kín được. Với $A=[0,1,1,0]$, bốn đoạn chứa cả vị trí $2$ và $3$ cùng với hai đoạn một phần tử chứa $1$ đều phủ kín được.
