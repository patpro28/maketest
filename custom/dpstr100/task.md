# DPSTR100 — Thông điệp chung

### Đề bài

Cho hai xâu chữ thường $A$ và $B$. Hãy tìm độ dài lớn nhất của một xâu là dãy con của cả $A$ và $B$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài dãy con chung dài nhất của $A$ và $B$. Nếu không có ký tự chung, in $0$.

### Ràng buộc

- $1\le N,M\le 1000$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 5
abcde
acebd
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 3
aaa
bbb
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, `ace` là một dãy con chung có độ dài $3$; không có dãy con chung dài hơn. Ở ví dụ 2, hai xâu không có ký tự chung, nên dãy con chung dài nhất là xâu rỗng.
