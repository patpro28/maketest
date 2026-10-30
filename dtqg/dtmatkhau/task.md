# DTMATKHAU — Đường đi có thể đối xứng

### Đề bài

Cho một cây có $N$ đỉnh, đặt gốc tại đỉnh $1$. Mỗi cạnh mang một chữ cái từ `a` tới `j` và có độ dài $1$. Với hai đỉnh $x,y$, gọi $\operatorname{LCA}(x,y)$ là tổ tiên chung sâu nhất và $\operatorname{dist}(x,y)$ là số cạnh trên đường đi duy nhất giữa chúng.

Mỗi đỉnh $u$ có một ngưỡng $K_u$. Với từng $u$, hãy đếm số cặp đỉnh không thứ tự $\{x,y\}$ thỏa mãn:

- $x\ne y$ và $\operatorname{LCA}(x,y)=u$.
- $\operatorname{dist}(x,y)\le K_u$.
- Các chữ trên đường đi giữa $x,y$ có thể được hoán vị thành một xâu đối xứng: một xâu đọc từ trái sang phải giống như đọc từ phải sang trái.

Không yêu cầu các chữ theo thứ tự sẵn có trên đường đi đã đối xứng. Mỗi cạnh trên đường đóng góp đúng một chữ; không được xóa hoặc thêm chữ. Cho phép một đầu mút bằng $u$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $K_1,K_2,\ldots,K_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$ và một ký tự $c$, mô tả một cạnh hai chiều mang chữ $c$.

### Dữ liệu ra

In $N$ dòng. Dòng thứ $u$ chứa số cặp hợp lệ có LCA bằng $u$. Không lấy phần dư theo modulo.

### Ràng buộc

- $1\le N\le10^5$.
- $0\le K_u\le N$.
- Mọi ký tự cạnh thuộc tập `a`, `b`, ..., `j`.
- Mọi chỉ số đỉnh của cạnh thuộc đoạn $[1,N]$; các cạnh tạo thành một cây.
- Đáp án có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
5
3 1 2 0 5
1 2 a
1 3 b
3 4 a
3 5 b
```

### Sample Output 1

```text
5
0
2
0
0
```

### Sample Input 2

```text
4
3 2 1 0
1 2 a
2 3 a
3 4 a
```

### Sample Output 2

```text
3
2
1
0
```

### Sample Input 3

```text
4
2 0 0 0
1 2 a
1 3 a
1 4 b
```

### Sample Output 3

```text
4
0
0
0
```

### Giải thích

Ở ví dụ 1, năm cặp được tính tại đỉnh $1$ là $\{1,2\}$, $\{1,3\}$, $\{1,5\}$, $\{2,4\}$, $\{2,5\}$. Đường $2\to1\to3\to4$ có các chữ `aba`; đường $2\to1\to3\to5$ có các chữ `abb`, có thể đổi thành `bab`. Tại đỉnh $3$, hai cặp hợp lệ là $\{3,4\}$ và $\{3,5\}$.

Ở ví dụ 2, mọi đường chỉ gồm chữ `a`, nên đều thỏa điều kiện hoán vị. Các cặp có LCA bằng một đỉnh trên cây dây phải chứa chính đỉnh đó làm một đầu mút.

Ở ví dụ 3, ba cặp giữa gốc và một lá đều hợp lệ. Cặp $\{2,3\}$ có chữ `aa` cũng hợp lệ; hai cặp lá còn lại có chữ `ab` và không hợp lệ.
