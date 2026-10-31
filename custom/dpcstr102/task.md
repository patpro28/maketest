# DPSTR102 — Xóa để giống nhau

### Đề bài

Cho hai xâu chữ thường $A$ và $B$. Mỗi thao tác xóa một ký tự ở một trong hai xâu. Hãy tìm tổng số thao tác ít nhất để hai xâu còn lại bằng nhau. Được phép xóa hết cả hai xâu để cùng thu được xâu rỗng.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In tổng số ký tự ít nhất cần xóa khỏi hai xâu.

### Ràng buộc

- $1\le N,M\le 1000$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 3
sea
eat
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 3
aaa
aaa
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, xóa chữ `s` khỏi `sea` và chữ `t` khỏi `eat`, cả hai còn `ea`, cần $2$ thao tác. Ở ví dụ 2, hai xâu đã bằng nhau.
