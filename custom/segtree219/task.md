# SEGTREE219 — Tổng theo hệ số cố định

### Đề bài

Có $N$ thiết bị. Thiết bị $i$ có mức tiêu thụ hiện tại $A_i$ và hệ số cố định $W_i$. Giá trị đóng góp của thiết bị là $A_iW_i$.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào mức tiêu thụ của từng thiết bị trong đoạn $[L,R]$.
- `2 L R`. In tổng giá trị đóng góp $\sum_{i=L}^{R}A_iW_i$ của đoạn hiện tại.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Dòng thứ ba chứa $N$ số nguyên $W_1,\dots,W_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10000$ ở đầu vào.
- $0\le W_i\le10000$.

### Sample Input 1

```text
4 4
2 1 3 4
0 2 5 1
2 1 4
1 2 4 -2
2 1 4
2 1 2
```

### Sample Output 1

```text
21
5
-2
```

### Sample Input 2

```text
3 3
0 1 2
0 0 10000
1 1 3 10000
2 1 2
2 2 3
```

### Sample Output 2

```text
0
100020000
```

### Giải thích

Ở ví dụ 1, ban đầu tổng là $0+2+15+4=21$. Sau cập nhật, mức tiêu thụ là $[2,-1,1,2]$, cho tổng $5$. Hai thiết bị đầu đóng góp $0$ và $-2$.

Ở ví dụ 2, hai thiết bị đầu có hệ số $0$. Thiết bị cuối có mức tiêu thụ $10002$ và đóng góp $100020000$.
