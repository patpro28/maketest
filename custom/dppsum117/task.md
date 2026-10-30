# PREFIX17 — Các nhóm ký tự

### Đề bài

Cho chuỗi $S$ gồm $N$ chữ cái tiếng Anh viết thường, đánh số từ $1$ đến $N$. Một nhóm là một đoạn ký tự giống nhau liên tiếp và dài nhất có thể trong đoạn đang xét. Ví dụ, chuỗi `aabbba` có ba nhóm: `aa`, `bbb`, `a`. Với mỗi truy vấn $L,R$, hãy đếm số nhóm trong chuỗi con từ vị trí $L$ đến $R$. Các nhóm chỉ được xét bên trong chuỗi con đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa chuỗi $S$ gồm $N$ ký tự.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số nhóm ký tự trong chuỗi con được hỏi.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $S$ chỉ gồm các chữ cái từ `a` đến `z`.
- $1\le L\le R\le N$.

### Sample Input 1

```text
6 3
aabbba
1 6
2 5
3 4
```

### Sample Output 1

```text
3
2
1
```

### Sample Input 2

```text
1 1
z
1 1
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, cả chuỗi có ba nhóm `aa`, `bbb`, `a`; đoạn $[2,5]$ là `abbb` có hai nhóm; đoạn $[3,4]$ là `bb` có một nhóm. Ở ví dụ 2, chuỗi một ký tự có một nhóm.
