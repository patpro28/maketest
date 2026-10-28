# SEGTREE125 — Ký tự thứ k trong văn bản nén

### Đề bài

Một văn bản được biểu diễn bởi $N$ khối theo thứ tự. Khối $i$ chứa $c_i$ lần lặp liên tiếp ký tự $s_i$. Văn bản đầy đủ là phép nối các khối theo chỉ số tăng dần. Khối có $c_i=0$ không đóng góp ký tự nào nhưng vẫn giữ chỉ số của nó.

Thực hiện các thao tác:

- `1 i d x`: đồng thời đổi ký tự của khối $i$ thành $d$ và số lần lặp thành $x$.
- `2 k`: tìm ký tự thứ $k$ trong văn bản đầy đủ, đánh số từ $1$. Nếu tồn tại, in ký tự đó, chỉ số khối chứa nó và thứ tự của ký tự bên trong khối, cũng đánh số từ $1$. Nếu văn bản có ít hơn $k$ ký tự, chỉ in `-1`.

Các khối kề nhau có cùng ký tự vẫn giữ nguyên chỉ số riêng, không gộp lại.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa chuỗi $s$ gồm đúng $N$ ký tự; ký tự thứ $i$ là $s_i$.
- Dòng thứ ba chứa $N$ số nguyên $c_1,\ldots,c_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in `-1` nếu không tồn tại ký tự. Nếu có, in ba giá trị cách nhau bởi dấu cách: ký tự, chỉ số khối và thứ tự bên trong khối. Mỗi đáp án nằm trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le c_i,x\le10^9$; $1\le k\le10^{18}$; $1\le i\le N$.
- $s_i,d\in\{\texttt{a},\ldots,\texttt{z}\}$.

### Sample Input 1

```text
4 7
aabc
2 0 3 1
2 2
2 3
2 6
2 7
1 2 z 2
2 3
2 5
```

### Sample Output 1

```text
a 1 2
b 3 1
c 4 1
-1
z 2 1
b 3 1
```

### Sample Input 2

```text
1 5
x
0
2 1
1 1 z 1000000000
2 1000000000
2 1000000001
2 1000000000000000000
```

### Sample Output 2

```text
-1
z 1 1000000000
-1
-1
```

### Giải thích

Ở ví dụ 1, văn bản ban đầu là `aabbbc`. Ký tự thứ $3$ là `b`, ở khối $3$ và đứng đầu khối này. Sau cập nhật, văn bản là `aazzbbbc`; ký tự thứ $3$ là `z` trong khối $2$, còn ký tự thứ $5$ là `b` trong khối $3$. Ở ví dụ 2, văn bản ban đầu rỗng; sau cập nhật có đúng $10^9$ ký tự `z` trong khối duy nhất.
