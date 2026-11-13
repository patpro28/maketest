# DPALL0002 — Bản ghi chung

### Đề bài

Cho hai xâu chữ thường $A$ và $B$. Một dãy con của một xâu được tạo bằng cách xóa một số ký tự và giữ nguyên thứ tự của các ký tự còn lại. Có thể không xóa ký tự nào hoặc xóa hết xâu.

Hãy tìm độ dài lớn nhất của một xâu là dãy con của cả $A$ và $B$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$ là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$.
- Dòng thứ ba chứa xâu $B$.

### Dữ liệu ra

In độ dài dãy con chung dài nhất.

### Ràng buộc

- $1\le N,M\le2000$.
- Các xâu chỉ gồm chữ cái thường từ `a` đến `z`.

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
3 4
abc
zzzz
```

### Sample Output 2

```text
0
```

### Giải thích

- Ví dụ 1. Có thể chọn dãy con chung `ace` dài $3$. Không có dãy con chung dài hơn.
- Ví dụ 2. Hai xâu không có chữ cái chung nên đáp án bằng $0$.
