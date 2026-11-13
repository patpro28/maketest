# DPSTR350 — Đúng số nhóm được chọn

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$, xâu đích $B$ có độ dài $M$ và số nguyên $K$. Sau khi chọn $M$ vị trí tăng dần trong $A$ tạo thành $B$, chia các vị trí được chọn thành các **nhóm liên tiếp tối đại**. Hai vị trí được chọn thuộc cùng nhóm khi mọi vị trí nằm giữa chúng cũng được chọn.

Hãy đếm số cách chọn tạo thành $B$ và có **đúng $K$ nhóm**. Mỗi nhóm không rỗng; hai nhóm khác nhau phải được ngăn bởi ít nhất một vị trí không chọn. Với $M\ge1$, một cách chọn hợp lệ không thể có $0$ nhóm.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,K$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số cách thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le2000$.
- $0\le K\le5$.
- $A,B$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 3 2
aaaaa
aaa
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
6 3 1
abcabc
abc
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, sáu bộ vị trí là $(1,2,4),(1,2,5),(1,3,4),(1,4,5),(2,3,5),(2,4,5)$. Mỗi bộ gồm đúng hai nhóm liên tiếp. Ở ví dụ 2, chỉ có $(1,2,3)$ và $(4,5,6)$ tạo được `abc` trong một nhóm.
