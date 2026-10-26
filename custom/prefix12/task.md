# PREFIX12 — Đếm chữ trong đoạn

### Đề bài

Cho chuỗi $S$ gồm $N$ chữ cái tiếng Anh viết thường. Các ký tự được đánh số từ $1$ đến $N$. Mỗi truy vấn gồm $L,R,c$, trong đó $c$ là một chữ cái tiếng Anh viết thường. Hãy đếm số lần xuất hiện của $c$ trong đoạn ký tự từ $L$ đến $R$, tính cả hai đầu mút.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa chuỗi $S$ gồm $N$ ký tự.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ và ký tự $c$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số lần xuất hiện của ký tự $c$ trong đoạn.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $S$ chỉ gồm các chữ cái từ `a` đến `z`.
- $1\le L\le R\le N$.
- $c$ là một chữ cái từ `a` đến `z`.

### Sample Input 1

```text
6 3
abacaa
1 6 a
2 5 b
3 4 z
```

### Sample Output 1

```text
4
1
0
```

### Sample Input 2

```text
1 2
z
1 1 z
1 1 a
```

### Sample Output 2

```text
1
0
```

### Giải thích

Ở ví dụ 1, chữ `a` xuất hiện bốn lần trong cả chuỗi, chữ `b` xuất hiện một lần trong đoạn $[2,5]$, còn chữ `z` không xuất hiện. Ở ví dụ 2, ký tự duy nhất là `z`.
