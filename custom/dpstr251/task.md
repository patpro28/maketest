# DPSTR251 — Hai mảnh thông điệp

### Đề bài

Cho hai xâu chữ thường $A,B$. Trong mỗi xâu, chọn đúng hai đoạn con liên tiếp không rỗng. Hai đoạn trong cùng một xâu không được giao nhau và phải được chọn theo thứ tự từ trái sang phải; chúng được phép đứng sát nhau hoặc có khoảng trống ở giữa.

Nội dung đoạn thứ nhất của $A$ phải bằng đoạn thứ nhất của $B$; nội dung đoạn thứ hai của $A$ phải bằng đoạn thứ hai của $B$. Không yêu cầu hai mảnh khác nhau về nội dung.

Hãy tìm tổng độ dài hai mảnh lớn nhất. Nếu không thể chọn đủ hai mảnh không rỗng, in $-1$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In tổng độ dài hai mảnh lớn nhất, hoặc $-1$ nếu không tồn tại phương án.

### Ràng buộc

- $1\le N,M\le4000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 5
abxcd
abycd
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
1 1
a
a
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, chọn mảnh thứ nhất `ab` và mảnh thứ hai `cd`, tổng độ dài $4$. Có thể bỏ ký tự giữa hai mảnh nhưng không được bỏ ký tự bên trong từng mảnh. Ở ví dụ 2, mỗi xâu chỉ có một ký tự nên không đủ hai đoạn không rỗng.
