# DUONGMIN — Các hậu tố trên đường tổ tiên

### Đề bài

Có một cây gồm $N$ đỉnh, đánh số từ $1$ đến $N$, được đặt gốc tại đỉnh $1$. Đỉnh $u$ mang giá trị $A_u$. Độ sâu của một đỉnh là số đỉnh trên đường từ gốc tới đỉnh đó; gốc có độ sâu $1$.

Mỗi truy vấn gồm một đỉnh $v$ và số nguyên $k$ không vượt quá độ sâu của $v$. Lấy $k$ đỉnh cuối trên đường từ gốc tới $v$. Theo thứ tự từ tổ tiên xuống $v$, gọi các giá trị của chúng là $B_1,B_2,\ldots,B_k$.

Bạn cần tính tổng cực tiểu của các hậu tố của dãy này:

$$\sum_{i=1}^{k}\min(B_i,B_{i+1},\ldots,B_k).$$

Mỗi hậu tố đều kết thúc tại $v$. Đây không phải tổng cực tiểu của mọi đoạn con trên đường đi. Các truy vấn độc lập và không thay đổi cây hoặc giá trị đỉnh.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh hai chiều của cây.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $v,k$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in tổng cần tìm trên một dòng, theo thứ tự truy vấn trong dữ liệu vào.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $0\le A_u\le10^9$.
- Các cạnh tạo thành một cây có gốc $1$.
- $1\le v\le N$; $1\le k\le\operatorname{depth}(v)$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
5 5
5 2 4 1 3
1 2
2 3
2 4
4 5
3 3
3 2
5 4
5 2
1 1
```

### Sample Output 1

```text
8
6
6
4
5
```

### Sample Input 2

```text
3 3
7 7 7
1 2
2 3
3 3
3 2
2 1
```

### Sample Output 2

```text
21
14
7
```

### Sample Input 3

```text
3 3
0 10 1
1 2
1 3
2 2
3 2
1 1
```

### Sample Output 3

```text
10
1
0
```

### Giải thích

Ở ví dụ 1, đường tới đỉnh $3$ có dãy $[5,2,4]$. Với $k=3$, các cực tiểu hậu tố là $2,2,4$, tổng bằng $8$. Với $k=2$, dãy được lấy là $[2,4]$, cho tổng $2+4=6$. Đường tới đỉnh $5$ có dãy $[5,2,1,3]$; tổng cực tiểu của bốn hậu tố bằng $1+1+1+3=6$.

Ở ví dụ 2, mọi cực tiểu đều bằng $7$, nên đáp án truy vấn là $7k$.

Ở ví dụ 3, hai đỉnh lá thuộc hai nhánh khác nhau; mỗi truy vấn chỉ xét đường tổ tiên của đỉnh được hỏi.
