# DPSTR152 — Thông điệp không lặp cạnh nhau

### Đề bài

Cho hai xâu $A,B$ chỉ gồm các chữ `a`, `b`, `c`. Hãy tìm độ dài lớn nhất của một dãy con chung sao cho hai ký tự liên tiếp bất kỳ trong dãy được chọn luôn khác nhau. Điều kiện liên tiếp được xét trong dãy con sau khi bỏ các vị trí không chọn.

Xâu rỗng và xâu một ký tự đều hợp lệ.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài lớn nhất của dãy con chung thỏa mãn điều kiện.

### Ràng buộc

- $1\le N,M\le 250$.
- $A,B$ chỉ gồm các chữ `a`, `b`, `c`.

### Sample Input 1

```text
5 5
aabbc
aabbc
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4 3
aaaa
aaa
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, chọn `abc` được độ dài $3$; không thể giữ hai chữ `a` hoặc hai chữ `b` liên tiếp. Ở ví dụ 2, mọi ký tự đều là `a`, nên chỉ giữ được tối đa một ký tự.
