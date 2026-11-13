# DPSTR332 — Các ký tự cách nhau

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$ và xâu đích $B$ có độ dài $M$. Hãy đếm số cách chọn $M$ vị trí $p_1<\cdots<p_M$ trong $A$ tạo thành $B$, sao cho không có hai vị trí được chọn nào kề nhau: $p_{j+1}-p_j\ge2$ với mọi $1\le j<M$.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số cách thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le5000$.
- $A,B$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 2
aaaaa
aa
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
3 3
abc
abc
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, các cặp là $(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)$. Ở ví dụ 2, muốn tạo `abc` phải lấy cả ba vị trí, vi phạm điều kiện không kề nhau.
