# DPSTR132 — Thông điệp kết thúc đúng chữ

### Đề bài

Cho hai xâu chữ thường $A,B$ và một chữ cái thường $C$. Hãy tìm độ dài lớn nhất của một dãy con chung của $A$ và $B$ kết thúc bằng chữ $C$. Dãy được chọn phải không rỗng. Nếu không có dãy nào thỏa mãn, in $-1$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa một chữ cái thường $C$.

### Dữ liệu ra

In độ dài lớn nhất của dãy con chung kết thúc bằng $C$, hoặc $-1$ nếu không tồn tại.

### Ràng buộc

- $1\le N,M\le 600$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $C$ là một chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 5
abaca
bacab
c
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 3
abc
abc
z
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, `bac` là dãy con chung dài nhất kết thúc bằng `c`, có độ dài $3$. Ở ví dụ 2, cả hai xâu đều không chứa `z` nên không thể tạo dãy con yêu cầu.
