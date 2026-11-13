# TDIFF009 — Tìm phép cộng đoạn

### Đề bài

Cho hai dãy số nguyên $A,B$, mỗi dãy gồm $N$ phần tử. Một phép cập nhật chọn đoạn không rỗng $[L,R]$ và số nguyên $X\ne0$, rồi cộng $X$ vào mọi phần tử của đoạn đó trong $A$.

Hãy tìm một phép cập nhật biến $A$ thành $B$ hoặc xác định rằng không có phép cập nhật như vậy.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Dòng thứ ba chứa $N$ số nguyên $B_1,B_2,\ldots,B_N$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, nếu có phép cập nhật, in ba số nguyên $L,R,X$ trên một dòng. Nếu không có, in `-1` trên một dòng.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|A_i|,|B_i|\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
3
5
3 -1 2 0 -4
3 4 7 5 -4
3
1 1 1
3 1 3
1
7
7
```

### Sample Output 1

```text
2 4 5
-1
-1
```

### Sample Input 2

```text
2
4
5 5 2 0
5 2 -1 -3
1
-1000000000
1000000000
```

### Sample Output 2

```text
2 4 -3
1 1 2000000000
```

### Giải thích

Trong ví dụ 1, ở bộ thứ nhất, cộng $5$ vào $[2,4]$ biến $A$ thành $B$. Ở bộ thứ hai, hai vị trí cần thay đổi là $1$ và $3$, còn vị trí $2$ phải giữ nguyên. Ở bộ thứ ba, hai dãy đã bằng nhau, trong khi phép cập nhật phải có $X\ne0$.

Trong ví dụ 2, bộ thứ nhất cần cộng $-3$ vào đoạn $[2,4]$. Bộ thứ hai cần cộng $2\cdot10^9$ vào vị trí duy nhất.
