# SEGTREE012 — Thu và chi

### Đề bài

Một sổ giao dịch có $N$ giao dịch được đánh số từ $1$ đến $N$. Giá trị giao dịch $i$ là $A_i$: nếu $A_i>0$ thì đây là khoản thu $A_i$ đồng; nếu $A_i<0$ thì đây là khoản chi $|A_i|$ đồng; nếu $A_i=0$ thì không có khoản thu hay chi.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: sửa giá trị giao dịch $i$ thành $x$.
- `2 l r`: tính riêng tổng tiền thu và tổng tiền chi của các giao dịch từ $l$ đến $r$.

Tổng tiền chi phải được biểu diễn bằng số không âm. Mỗi truy vấn sử dụng các giá trị sau tất cả thao tác sửa trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả giá trị ban đầu của các giao dịch.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm hai số nguyên không âm: tổng tiền thu rồi đến tổng tiền chi trong đoạn được hỏi. Hai số cách nhau một dấu cách. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
5 7
10 -4 0 -6 3
2 1 5
2 2 4
1 2 7
2 1 3
1 1 -8
2 1 5
2 3 3
```

### Sample Output 1

```text
13 10
0 10
17 0
10 14
0 0
```

### Sample Input 2

```text
3 4
-1000000000 -1000000000 -1000000000
2 1 3
1 2 1000000000
2 1 3
2 2 2
```

### Sample Output 2

```text
0 3000000000
1000000000 2000000000
1000000000 0
```

### Giải thích

Ở ví dụ 1, ban đầu các khoản thu là $10,3$ và các khoản chi là $4,6$, nên truy vấn đầu cho kết quả $13,10$. Đoạn $[2,4]$ chỉ có các khoản chi và một giao dịch bằng $0$. Sau khi sửa giao dịch $2$ thành $7$, ba giao dịch đầu có tổng thu $17$ và tổng chi $0$. Sau lần sửa tiếp theo, cả sổ có tổng thu $7+3=10$ và tổng chi $8+6=14$. Giao dịch thứ $3$ không tạo ra thu hay chi.

Ở ví dụ 2, tổng chi ban đầu là $3\cdot10^9$. Sửa giao dịch thứ $2$ từ khoản chi thành khoản thu làm cả hai tổng thay đổi.
