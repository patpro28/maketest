# DPSTR331 — Chọn đủ vị trí đánh dấu

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$, xâu đích $B$ có độ dài $M$ và xâu nhị phân $C$ có độ dài $N$. Vị trí $i$ được đánh dấu nếu $C_i=1$.

Hãy đếm số cách chọn $M$ vị trí tăng dần trong $A$ để tạo thành $B$, sao cho **đúng $K$ vị trí được chọn** đã được đánh dấu. Không yêu cầu chọn hết các vị trí được đánh dấu.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,K$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa xâu nhị phân $C$ có đúng $N$ ký tự.

### Dữ liệu ra

In số cách thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le2500$.
- $0\le K\le5$.
- $A,B$ chỉ gồm chữ cái thường từ `a` đến `z`.
- $C$ chỉ gồm các ký tự `0` và `1`.

### Sample Input 1

```text
4 2 1
aaaa
aa
1010
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
3 2 1
aba
aa
101
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, có hai vị trí đánh dấu và hai vị trí không đánh dấu. Chọn một vị trí mỗi loại được $2\cdot2=4$ cách. Ở ví dụ 2, chỉ có thể chọn hai chữ `a` ở vị trí $1,3$, nhưng cả hai đều được đánh dấu nên không thỏa $K=1$.
