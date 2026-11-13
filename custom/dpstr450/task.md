# DPSTR450 — Chia xâu rồi sửa đối xứng

### Đề bài

Cho xâu $S$. Chia toàn bộ xâu thành đúng $K$ đoạn liên tiếp không rỗng. Sau khi chia, có thể thay ký tự trong mỗi đoạn để biến đoạn đó thành xâu đối xứng, tức đọc xuôi và ngược như nhau. Một lần thay một ký tự thành một chữ cái thường khác tốn một thao tác. Hãy tìm số thao tác ít nhất.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In tổng số lần thay ít nhất.

### Ràng buộc

- $1\le N\le500$ và $1\le K\le\min(N,100)$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 2
abc
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
6 2
abbaaa
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, một mảnh phải có hai chữ khác nhau, nên cần một lần thay. Ở ví dụ 2, `abba | aa` đã gồm hai đoạn đối xứng.
