# DPSTR652 — Những xâu đối xứng khác nhau

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Hãy đếm số xâu **không rỗng, có nội dung phân biệt**, vừa đối xứng vừa là dãy con của $S$.

Mỗi nội dung chỉ được tính một lần, bất kể có bao nhiêu bộ vị trí trong $S$ tạo được nội dung đó. Chẳng hạn, từ `aaa` chỉ có ba nội dung đối xứng phân biệt là `a`, `aa`, `aaa`.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

Một **dãy con** được tạo bằng cách xóa một số vị trí, có thể không xóa vị trí nào, và giữ nguyên thứ tự các ký tự còn lại. Các vị trí giữ lại không bắt buộc liên tiếp; mỗi vị trí chỉ được dùng một lần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số nội dung đối xứng phân biệt thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3
aaa
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4
bccb
```

### Sample Output 2

```text
6
```

### Giải thích

Ở ví dụ 1, chỉ có `a`, `aa`, `aaa`, nên kết quả là $3$ dù có nhiều cách chọn vị trí. Ở ví dụ 2, sáu nội dung là `b`, `c`, `bb`, `cc`, `bcb`, `bccb`.
