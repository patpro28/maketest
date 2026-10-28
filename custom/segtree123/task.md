# SEGTREE123 — Trung vị trên băng chuyền

### Đề bài

Cho dãy $a_1,\ldots,a_N$, trong đó mọi giá trị nằm trong $[1,M]$. Với mỗi đoạn liên tiếp có đúng $W$ phần tử, hãy tìm trung vị dưới của đoạn.

Nếu sắp các phần tử của một đoạn theo thứ tự không giảm thành $v_1,\ldots,v_W$, trung vị dưới là $v_{\lfloor(W+1)/2\rfloor}$. Các phần tử bằng nhau vẫn được tính riêng theo số lần xuất hiện.

In kết quả của các cửa sổ $[1,W]$, $[2,W+1]$, ..., $[N-W+1,N]$ theo thứ tự đó.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,W$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.

### Dữ liệu ra

In $N-W+1$ số nguyên trên một dòng, cách nhau bởi dấu cách, là các trung vị dưới theo thứ tự cửa sổ.

### Ràng buộc

- $1\le N,M\le200000$; $1\le W\le N$.
- $1\le a_i\le M$.

### Sample Input 1

```text
6 5 4
1 5 2 2 4 3
```

### Sample Output 1

```text
2 2 2
```

### Sample Input 2

```text
5 9 1
9 1 9 3 5
```

### Sample Output 2

```text
9 1 9 3 5
```

### Giải thích

Ở ví dụ 1, ba cửa sổ sau sắp xếp lần lượt là $(1,2,2,5)$, $(2,2,4,5)$ và $(2,2,3,4)$. Trung vị dưới là phần tử thứ $2$, đều bằng $2$. Ở ví dụ 2, mỗi cửa sổ chỉ có một phần tử nên kết quả chính là dãy ban đầu.
