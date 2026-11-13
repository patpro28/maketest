# DPSTR352 — Khoảng cách giữa hai ký tự

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$, xâu đích $B$ có độ dài $M$ và hai số nguyên $L,R$. Hãy đếm số cách chọn $M$ vị trí $p_1<\cdots<p_M$ trong $A$ tạo thành $B$, sao cho $L\le p_{j+1}-p_j\le R$ với mọi $1\le j<M$.

Khoảng cách ở đây là **hiệu hai chỉ số**, không phải số vị trí bị bỏ ở giữa. Nếu $M=1$, không có cặp vị trí liên tiếp nào cần kiểm tra; không có ràng buộc khoảng cách từ hai đầu xâu đến vị trí được chọn.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,M,L,R$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số cách thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le5000$.
- $1\le L\le R\le N$.
- $A,B$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 2 2 3
aaaaa
aa
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
6 3 1 1
abcabc
abc
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, có ba cặp cách nhau $2$ vị trí và hai cặp cách nhau $3$ vị trí, tổng cộng $5$. Ở ví dụ 2, khoảng cách bắt buộc bằng $1$, nên chỉ lấy được hai lần xuất hiện liên tiếp của `abc`.
