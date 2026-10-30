# DTBASAC — Bộ ba khác màu

### Đề bài

Cho một cây có $N$ đỉnh, đánh số từ $1$ tới $N$, đặt gốc tại đỉnh $1$. Đỉnh $v$ có màu $C_v$. Cây con của một đỉnh gồm chính đỉnh đó và mọi hậu duệ của nó.

Với mỗi đỉnh $u$, hãy đếm số cách chọn ba đỉnh phân biệt trong cây con $u$ sao cho màu của chúng đôi một khác nhau. Không phân biệt thứ tự ba đỉnh được chọn; các đỉnh có cùng màu vẫn là các đỉnh khác nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $C_1,C_2,\ldots,C_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh hai chiều của cây.

### Dữ liệu ra

In $N$ dòng. Dòng thứ $u$ chứa số bộ ba hợp lệ trong cây con $u$. Không lấy phần dư theo modulo.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le C_v\le10^9$.
- Mọi chỉ số đỉnh thuộc đoạn $[1,N]$; các cạnh tạo thành một cây.
- Đáp án có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
5
1 2 1 3 2
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
4
0
1
0
0
```

### Sample Input 2

```text
4
1 2 3 4
1 2
2 3
3 4
```

### Sample Output 2

```text
4
1
0
0
```

### Sample Input 3

```text
3
7 7 7
1 2
1 3
```

### Sample Output 3

```text
0
0
0
```

### Giải thích

Ở ví dụ 1, cây con gốc có hai đỉnh màu $1$, hai đỉnh màu $2$ và một đỉnh màu $3$, nên có $2\cdot2\cdot1=4$ bộ ba. Cây con $3$ gồm các đỉnh $3,4,5$ mang ba màu khác nhau, tạo một bộ ba.

Ở ví dụ 2, mọi đỉnh khác màu. Cây con $1$ có $\binom43=4$ bộ ba, cây con $2$ có một bộ ba.

Ở ví dụ 3, mọi đỉnh cùng màu nên không có bộ ba hợp lệ.
