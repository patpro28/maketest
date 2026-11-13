# DPSTR351 — Bản tin có sai lệch

### Đề bài

Cho xâu nguồn $A$ có độ dài $N$, xâu đích $B$ có độ dài $M$ và số nguyên $K$. Chọn $M$ vị trí $p_1<\cdots<p_M$ trong $A$. Vị trí thứ $j$ của dãy được chọn là một sai lệch nếu $A_{p_j}\ne B_j$.

Hãy đếm số cách chọn có **không quá $K$ sai lệch**. Chỉ đếm bộ vị trí; không tính thêm số cách sửa chữ. Không chèn hoặc xóa ký tự trong xâu đích.

Một cách chọn được xác định bởi bộ chỉ số tăng nghiêm ngặt của các vị trí được chọn. Các vị trí khác nhau tạo thành các cách khác nhau, kể cả khi cho cùng nội dung. Mỗi vị trí chỉ được chọn một lần; các vị trí được chọn không bắt buộc liên tiếp.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,K$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số cách thỏa mãn yêu cầu, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le2500$.
- $0\le K\le5$.
- $A,B$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 2 1
abc
ab
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
4 2 1
aaaa
bb
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, bộ $(1,2)$ tạo `ab` và không sai vị trí nào; bộ $(1,3)$ tạo `ac` và sai một vị trí. Bộ $(2,3)$ tạo `bc` và sai hai vị trí nên không được tính. Ở ví dụ 2, mọi cặp đều tạo `aa`, khác `bb` ở hai vị trí, vượt giới hạn $1$.
