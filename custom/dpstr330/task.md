# DPSTR330 — Dấu hỏi trong bản tin

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$, gồm chữ cái thường và dấu `?`, cùng xâu đích $B$ có độ dài $M$, chỉ gồm chữ cái thường. Trước tiên, thay **mọi** dấu `?` của $A$ bằng một chữ cái từ `a` đến `z`. Sau đó chọn $M$ vị trí tăng dần để tạo thành $B$.

Hãy đếm số cặp gồm **một cách thay toàn bộ dấu hỏi** và **một bộ vị trí được chọn** hợp lệ. Hai cách thay khác nhau ở dấu hỏi không được chọn vẫn được tính riêng.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số cách thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le5000$.
- $A$ gồm chữ cái thường từ `a` đến `z` và dấu `?`; $B$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
2 1
??
a
```

### Sample Output 1

```text
52
```

### Sample Input 2

```text
3 2
?a?
aa
```

### Sample Output 2

```text
53
```

### Giải thích

Ở ví dụ 1, nếu chọn vị trí thứ nhất thì dấu hỏi ở đó phải thành `a`, còn dấu hỏi thứ hai có $26$ lựa chọn. Chọn vị trí thứ hai cũng có $26$ cách, tổng cộng $52$. Ở ví dụ 2, chọn $(1,2)$ hoặc $(2,3)$ cho $26$ cách mỗi bộ; chọn $(1,3)$ cho đúng một cách, tổng $53$.
