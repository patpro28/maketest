# DPSTR551 — Chỉnh sửa trong ngân sách

### Đề bài

Cho hai xâu $A,B$. Trong một thao tác, bạn có thể xóa một ký tự của xâu hiện tại, chèn một chữ cái thường ở vị trí bất kỳ hoặc thay một ký tự bằng một chữ cái thường khác. Hãy tìm số thao tác ít nhất để biến $A$ thành $B$. Bạn chỉ được dùng tối đa $K$ thao tác. Nếu không thể biến đổi trong ngân sách, hãy báo không có phương án.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,K$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số thao tác ít nhất nếu không vượt $K$, ngược lại in $-1$.

### Ràng buộc

- $1\le N,M\le200000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le K\le50$.

### Sample Input 1

```text
4 4 2
abba
bbaa
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 5 1
abc
abcde
```

### Sample Output 2

```text
-1
```

### Giải thích

Ví dụ 1 thay chữ ở vị trí thứ nhất và thứ ba. Ví dụ 2 cần ít nhất hai lần chèn do hai xâu chênh hai ký tự.
