# PREFIX024 — Ba loại ký tự

### Đề bài

Cho chuỗi $S$ gồm $N$ ký tự, mỗi ký tự là `a`, `b` hoặc `c`. Các vị trí được đánh số từ $1$. Mỗi truy vấn gồm hai chỉ số $L,R$. Hãy đếm riêng số lần xuất hiện của từng ký tự `a`, `b`, `c` trong chuỗi con từ $L$ đến $R$, tính cả hai đầu mút.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa chuỗi $S$ gồm $N$ ký tự.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in ba số nguyên trên một dòng, lần lượt là số lần xuất hiện của `a`, `b`, `c` trong chuỗi con được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $S$ chỉ gồm các ký tự `a`, `b`, `c`.
- $1\le L\le R\le N$ trong mọi truy vấn.

### Sample Input 1

```text
6 3
abacbc
1 6
2 4
3 3
```

### Sample Output 1

```text
2 2 2
1 1 1
1 0 0
```

### Sample Input 2

```text
1 1
a
1 1
```

### Sample Output 2

```text
1 0 0
```

### Giải thích

Ở ví dụ 1: Với đoạn $[1,6]$, số ký tự `a`, `b`, `c` lần lượt là $2,2,2$. Với đoạn $[2,4]$, số ký tự `a`, `b`, `c` lần lượt là $1,1,1$. Với đoạn $[3,3]$, số ký tự `a`, `b`, `c` lần lượt là $1,0,0$.

Ở ví dụ 2: Với đoạn $[1,1]$, số ký tự `a`, `b`, `c` lần lượt là $1,0,0$.
