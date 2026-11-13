# DPSTR303 — Tạo xâu đích

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$ và xâu đích $B$ có độ dài $M$. Hãy đếm số cách chọn $M$ vị trí $p_1<p_2<\cdots<p_M$ trong $A$ sao cho $A_{p_j}=B_j$ với mọi $j$.

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
4 2
aaaa
aa
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
6 3
abcdef
ace
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, chọn bất kỳ hai trong bốn vị trí đều tạo được `aa`, có $6$ cách. Ở ví dụ 2, chỉ có bộ $(1,3,5)$ tạo được `ace`; các vị trí không cần liên tiếp.
