# DPSTR103 — Bản ghi hợp nhất

### Đề bài

Cho hai xâu chữ thường $A$ và $B$. Hãy tìm độ dài nhỏ nhất của một xâu $T$ sao cho cả $A$ và $B$ đều là dãy con của $T$. Bạn chỉ cần in độ dài, không cần xây dựng xâu $T$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài nhỏ nhất của xâu $T$ thỏa mãn yêu cầu.

### Ràng buộc

- $1\le N,M\le 1000$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
2 2
ab
ac
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 2
aaa
aa
```

### Sample Output 2

```text
3
```

### Giải thích

Ở ví dụ 1, có thể chọn $T=$ `abc`, độ dài $3$. Xâu độ dài $2$ không thể chứa cả hai xâu khác nhau `ab` và `ac` làm dãy con. Ở ví dụ 2, chọn $T=$ `aaa`.
