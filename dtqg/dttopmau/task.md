# DTTOPMAU — Những màu phổ biến nhất

### Đề bài

Cho một cây có $N$ đỉnh, đặt gốc tại đỉnh $1$. Đỉnh $v$ có màu $C_v$. Cây con của một đỉnh gồm chính đỉnh đó và mọi hậu duệ của nó.

Có $Q$ truy vấn độc lập. Truy vấn $(u,k)$ yêu cầu chọn tối đa $k$ màu xuất hiện trong cây con $u$, sao cho số đỉnh trong cây con $u$ mang các màu được chọn là lớn nhất. Hãy in số đỉnh lớn nhất đó.

Nếu $k=0$, đáp án bằng $0$. Nếu $k$ không nhỏ hơn số màu phân biệt trong cây con, có thể chọn tất cả các màu. Các truy vấn không thay đổi cây hoặc màu của đỉnh.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $C_1,C_2,\ldots,C_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh hai chiều của cây.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,k$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in số đỉnh lớn nhất có thể thu được trên một dòng, theo thứ tự đầu vào.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $1\le C_v\le10^9$.
- Với mỗi truy vấn: $1\le u\le N$, $0\le k\le N$.
- Mọi chỉ số đỉnh của cạnh thuộc đoạn $[1,N]$; các cạnh tạo thành một cây.

### Sample Input 1

```text
5 5
1 2 1 3 2
1 2
1 3
3 4
3 5
1 2
3 2
3 5
2 0
1 5
```

### Sample Output 1

```text
4
2
3
0
5
```

### Sample Input 2

```text
1 3
1000000000
1 0
1 1
1 1
```

### Sample Output 2

```text
0
1
1
```

### Sample Input 3

```text
4 3
8 8 8 8
1 2
1 3
1 4
1 1
1 4
4 2
```

### Sample Output 3

```text
4
4
1
```

### Giải thích

Ở ví dụ 1, truy vấn đầu chọn màu $1$ và $2$, phủ bốn đỉnh. Cây con $3$ có ba màu, mỗi màu xuất hiện một lần, nên chọn hai màu phủ hai đỉnh. Chọn tối đa năm màu trong cây con này phủ cả ba đỉnh.

Ở ví dụ 2, không chọn màu thì phủ không đỉnh; chọn màu duy nhất thì phủ một đỉnh.

Ở ví dụ 3, cả cây chỉ có một màu. Chọn màu đó đủ phủ mọi đỉnh trong cây con được hỏi.
