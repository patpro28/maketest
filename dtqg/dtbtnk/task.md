# DTBTNK — Biểu thức ngoặc bậc k

### Đề bài

Một biểu thức ngoặc là xâu chỉ gồm `(` và `)`. Biểu thức ngoặc đúng và bậc của nó được định nghĩa như sau:

- Xâu rỗng là biểu thức ngoặc đúng, có bậc $0$.
- Nếu $A$ là biểu thức ngoặc đúng có bậc $h$, thì `(A)` là biểu thức ngoặc đúng có bậc $h+1$.
- Nếu $A,B$ là hai biểu thức ngoặc đúng có bậc $h_1,h_2$, thì xâu ghép $AB$ có bậc $\max(h_1,h_2)$.

Tương đương, bậc là độ sâu lồng ngoặc lớn nhất. Ví dụ `()(())` có bậc $2$, còn `(()(()))` có bậc $3$.

Cho xâu $S$ và số nguyên dương $k$. Hãy đếm các **dãy con khác nhau về nội dung** của $S$ là biểu thức ngoặc đúng có bậc **đúng bằng $k$**.

Một dãy con nhận được bằng cách xóa không hoặc một số ký tự của $S$ và giữ nguyên thứ tự các ký tự còn lại; các vị trí được giữ không bắt buộc liên tiếp. Nếu nhiều cách chọn vị trí tạo cùng một xâu, chỉ tính xâu đó một lần.

### Dữ liệu vào

Đọc từ tệp `BTNK.INP`:

- Dòng đầu chứa xâu $S$.
- Dòng thứ hai chứa số nguyên $k$.

### Dữ liệu ra

Ghi ra tệp `BTNK.OUT` số dãy con thỏa mãn, lấy phần dư khi chia cho $111539786$.

### Ràng buộc

- $2\le n=|S|\le4000$.
- $S$ chỉ gồm các ký tự `(` và `)`.
- $1\le k\le\lfloor n/2\rfloor$.

### Sample Input 1

```text
()()
1
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
((()))
2
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, hai xâu được tính là `()` và `()()`. Dù `()` có thể được chọn bằng nhiều bộ vị trí, nó chỉ được tính một lần.

Ở ví dụ 2, chỉ xâu `(())` có bậc đúng bằng $2$.

### Nguồn

Chuyển từ `BTNK.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
