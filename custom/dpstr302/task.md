# DPSTR302 — Mẫu có chữ lặp

### Đề bài

Cho xâu $A$ gồm $N$ chữ cái thường. Hãy đếm số cách chọn ba chỉ số $p<q<r$ sao cho $A_pA_qA_r$ là `aba`.

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
4
```

### Sample Input 2

```text
3
aaa
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, bốn bộ chỉ số là $(1,2,3),(1,2,5),(1,4,5),(3,4,5)$. Hai chữ `a` của mẫu phải dùng hai vị trí khác nhau. Ở ví dụ 2, không có chữ `b` nên kết quả bằng $0$.
