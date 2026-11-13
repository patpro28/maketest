# DPSTR202 — Đoạn tin có dấu mốc

### Đề bài

Cho hai xâu chữ thường $A,B$ và chữ cái thường $C$. Tìm độ dài lớn nhất của một đoạn con liên tiếp chung có chứa ít nhất một chữ $C$. Nếu không có đoạn nào thỏa mãn, in $-1$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa chữ cái $C$.

### Dữ liệu ra

In độ dài lớn nhất của đoạn chung có chứa $C$, hoặc $-1$ nếu không tồn tại.

### Ràng buộc

- $1\le N,M\le5000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.
- $C$ là một chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 8
abaca
zzbacazz
a
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
4 4
axbc
abcd
x
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, `baca` là đoạn chung dài $4$ và chứa chữ `a`. Ở ví dụ 2, xâu thứ hai không có `x`, nên không tồn tại đoạn chung yêu cầu.
