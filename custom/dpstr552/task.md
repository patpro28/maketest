# DPSTR552 — Đoạn đích gần nhất

### Đề bài

Cho xâu nguồn $A$ và xâu $B$. Hãy chọn một đoạn liên tiếp không rỗng của $B$ để số lần chèn, xóa hoặc thay một ký tự cần dùng để biến $A$ thành đoạn đó là ít nhất. Mỗi thao tác tốn $1$.

Nếu có nhiều đoạn tối ưu, chọn đoạn có vị trí bắt đầu nhỏ nhất. Nếu vẫn còn hòa, chọn vị trí kết thúc nhỏ nhất. Vị trí trong $B$ đánh số từ $1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In ba số nguyên là số thao tác ít nhất, vị trí bắt đầu và vị trí kết thúc của đoạn được chọn.

### Ràng buộc

- $1\le N,M\le5000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
2 5
ab
zabab
```

### Sample Output 1

```text
0 2 3
```

### Sample Input 2

```text
1 2
a
bc
```

### Sample Output 2

```text
1 1 1
```

### Giải thích

Ví dụ 1 có hai đoạn `ab`, chọn đoạn $[2,3]$ vì bắt đầu sớm hơn. Ví dụ 2 có thể thay `a` thành `b` hoặc `c` với một thao tác, nên chọn $[1,1]$.
