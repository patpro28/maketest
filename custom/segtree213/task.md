# SEGTREE213 — Điểm theo vị trí

### Đề bài

Cho dãy điểm $A_1,\dots,A_N$. Khi đánh giá đoạn $[L,R]$, phần tử đầu đoạn có hệ số $1$, phần tử kế tiếp có hệ số $2$, và cứ tiếp tục như vậy đến hết đoạn.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào từng phần tử trong đoạn $[L,R]$.
- `2 L R`. In giá trị $\sum_{i=L}^{R}(i-L+1)A_i$ của đoạn hiện tại.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le1000$ ở đầu vào.

### Sample Input 1

```text
4 4
2 1 3 4
2 2 4
1 2 3 2
2 2 4
2 1 3
```

### Sample Output 1

```text
19
25
23
```

### Sample Input 2

```text
3 3
0 0 0
1 1 3 -2
2 2 3
2 3 3
```

### Sample Output 2

```text
-6
-2
```

### Giải thích

Ở ví dụ 1, đoạn $[2,4]$ ban đầu cho $1+2\cdot3+3\cdot4=19$. Sau cập nhật, đoạn đó là $[3,5,4]$ và cho $25$. Ba phần tử đầu cho $2+2\cdot3+3\cdot5=23$.

Ở ví dụ 2, hai phần tử trong đoạn $[2,3]$ nhận hệ số $1,2$, nên tổng là $-6$. Đoạn một phần tử dùng hệ số $1$.
