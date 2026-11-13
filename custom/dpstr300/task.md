# DPSTR300 — Những cặp ab

### Đề bài

Cho xâu $A$ gồm $N$ chữ cái thường. Hãy đếm số cách chọn hai chỉ số $p<q$ sao cho $A_p$ là `a` và $A_q$ là `b`, tức tạo thành dãy con `ab`.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.

### Dữ liệu ra

In số cách chọn thỏa mãn yêu cầu. Kết quả được in chính xác, không lấy modulo.

### Ràng buộc

- $1\le N\le200000$.
- $A$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5
ababa
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4
bbbb
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, ba cặp chỉ số hợp lệ là $(1,2),(1,4),(3,4)$. Ở ví dụ 2, không có chữ `a` nên không tạo được mẫu.
