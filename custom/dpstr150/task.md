# DPSTR150 — Ký tự bắt buộc

### Đề bài

Cho hai xâu chữ thường $A,B$ và một chữ cái thường $C$. Hãy tìm độ dài lớn nhất của một dãy con chung có ít nhất một ký tự $C$. Ký tự $C$ có thể nằm ở vị trí bất kỳ trong dãy được chọn và có thể xuất hiện nhiều lần. Nếu không có dãy con chung thỏa mãn, in $-1$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa một chữ cái thường $C$.

### Dữ liệu ra

In độ dài lớn nhất của dãy con chung có chứa $C$, hoặc $-1$ nếu không tồn tại.

### Ràng buộc

- $1\le N,M\le 300$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $C$ là một chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 3
abx
xab
x
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
4 4
abca
abca
b
```

### Sample Output 2

```text
4
```

### Giải thích

Ở ví dụ 1, LCS thông thường là `ab`, nhưng không chứa `x`. Dãy chung có chứa `x` dài nhất chỉ là `x`, độ dài $1$. Ở ví dụ 2, giữ cả xâu `abca`, có chứa `b`, độ dài $4$.
