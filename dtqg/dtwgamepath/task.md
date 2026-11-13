# DTWGAMEPATH — Bảng chữ đồng nhất

### Đề bài

Cho bảng chữ gồm $m$ hàng và $n$ cột, các hàng đánh số từ trên xuống và các cột đánh số từ trái sang phải, bắt đầu từ $1$. Mỗi ô chứa một chữ cái tiếng Anh thường hoặc ký tự `#` biểu thị ô cấm.

Bạn đi từ ô $(1,1)$ đến ô $(m,n)$. Mỗi bước chỉ được đi sang ô bên phải hoặc ô bên dưới; không được đi vào ô cấm. Ghép lần lượt ký tự của tất cả ô trên đường đi, kể cả hai đầu mút, được xâu $T$.

Cho xâu $S$. Một đường đi thắng cuộc nếu $T$ là xâu đối xứng và chứa $S$ như một **xâu con liên tiếp**. Xâu đối xứng là xâu đọc từ trái sang phải và từ phải sang trái giống nhau. Hai đường đi khác nhau nếu có một ô thuộc đường này nhưng không thuộc đường kia.

Hãy đếm số đường đi thắng cuộc, lấy phần dư khi chia cho $D$. Nếu một trong hai đầu mút là ô cấm thì không có đường đi hợp lệ.

Trong phiên bản này, $S$ chỉ có một ký tự; mọi ô không cấm đều chứa ký tự đó và ô $(1,1)$ không bị cấm.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $m,n,D$.
- Dòng thứ hai chứa xâu $S$.
- Trong $m$ dòng tiếp theo, dòng thứ $i$ chứa xâu gồm đúng $n$ ký tự mô tả hàng thứ $i$ của bảng; mỗi ký tự là chữ cái từ `a` đến `z` hoặc `#`.

### Dữ liệu ra

In một số nguyên là số đường đi thắng cuộc, lấy phần dư khi chia cho $D$.

### Ràng buộc

- $1\le m,n\le150$.
- $1\le D\le10^9$.
- $|S|=1$, $S$ là chữ cái từ `a` đến `z`.
- Mọi ô không cấm đều chứa ký tự $S$; ô $(1,1)$ không cấm.

### Sample Input 1

```text
2 3 100
a
aaa
aaa
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 3 100
b
bbb
b#b
bbb
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, có ba cách sắp xếp một bước xuống và hai bước sang phải. Cả ba xâu đều là `aaaa`.

Ở ví dụ 2, chỉ có hai đường vòng quanh ô cấm ở chính giữa. Cả hai đều tạo xâu `bbbbb`.

### Nguồn

Bài tự biên soạn, phiên bản luyện tập trước WGAMEPN — Trò chơi trên bảng chữ, dựa trên `wgamepn.pdf` do người dùng cung cấp.
