# DTHENGAP — Khoảng cách tại điểm gặp

### Đề bài

Cho một cây có $N$ đỉnh, đặt gốc tại đỉnh $1$. Mỗi cạnh có độ dài $1$. Với hai đỉnh $x,y$, gọi $\operatorname{dist}(x,y)$ là số cạnh trên đường đi duy nhất giữa chúng; $\operatorname{LCA}(x,y)$ là tổ tiên chung của chúng có độ sâu lớn nhất.

Mỗi đỉnh $u$ được cho một số $K_u$. Với từng $u$, hãy đếm số cặp đỉnh không thứ tự $\{x,y\}$ thỏa mãn:

- $x\ne y$.
- $\operatorname{LCA}(x,y)=u$.
- $\operatorname{dist}(x,y)=K_u$.

Cho phép một trong hai đầu mút bằng $u$. Một cặp chỉ được tính cho đúng đỉnh là LCA của nó. Khi $K_u=0$, không có cặp hợp lệ tại $u$ vì hai đầu mút phải khác nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $K_1,K_2,\ldots,K_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh hai chiều của cây.

### Dữ liệu ra

In $N$ dòng. Dòng thứ $u$ chứa số cặp hợp lệ có LCA bằng $u$. Không lấy phần dư theo modulo.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $0\le K_u\le N$.
- Mọi chỉ số đỉnh của cạnh thuộc đoạn $[1,N]$; các cạnh tạo thành một cây.
- Đáp án có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
5
2 1 2 0 5
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
3
0
1
0
0
```

### Sample Input 2

```text
4
3 2 1 0
1 2
2 3
3 4
```

### Sample Output 2

```text
1
1
1
0
```

### Sample Input 3

```text
4
2 1 1 1
1 2
1 3
1 4
```

### Sample Output 3

```text
3
0
0
0
```

### Giải thích

Ở ví dụ 1, ba cặp tính tại đỉnh $1$ là $\{1,4\}$, $\{1,5\}$ và $\{2,3\}$. Cặp $\{4,5\}$ cũng có khoảng cách $2$, nhưng được tính tại đỉnh $3$ vì LCA của nó bằng $3$.

Ở ví dụ 2, các cặp được tính lần lượt tại đỉnh $1,2,3$ là $\{1,4\}$, $\{2,4\}$, $\{3,4\}$.

Ở ví dụ 3, ba cặp giữa hai lá bất kỳ đều có khoảng cách $2$ và LCA bằng $1$.
