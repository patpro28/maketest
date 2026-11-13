# DTWGAMEPAL — Đường đi đối xứng

### Đề bài

Cho bảng chữ gồm $m$ hàng và $n$ cột, các hàng đánh số từ trên xuống và các cột đánh số từ trái sang phải, bắt đầu từ $1$. Mỗi ô chứa một chữ cái tiếng Anh thường hoặc ký tự `#` biểu thị ô cấm.

Bạn đi từ ô $(1,1)$ đến ô $(m,n)$. Mỗi bước chỉ được đi sang ô bên phải hoặc ô bên dưới; không được đi vào ô cấm. Ghép lần lượt ký tự của tất cả ô trên đường đi, kể cả hai đầu mút, được xâu $T$.

Cho xâu $S$. Một đường đi thắng cuộc nếu $T$ là xâu đối xứng và chứa $S$ như một **xâu con liên tiếp**. Xâu đối xứng là xâu đọc từ trái sang phải và từ phải sang trái giống nhau. Hai đường đi khác nhau nếu có một ô thuộc đường này nhưng không thuộc đường kia.

Hãy đếm số đường đi thắng cuộc, lấy phần dư khi chia cho $D$. Nếu một trong hai đầu mút là ô cấm thì không có đường đi hợp lệ.

Trong phiên bản này, $S$ chỉ có một ký tự và trùng với ký tự ở ô $(1,1)$; do đó chỉ cần đếm các đường đi tạo xâu đối xứng.

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
- Ô $(1,1)$ chứa đúng ký tự $S$.

### Sample Input 1

```text
2 2 100
a
ab
aa
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
2 3 100
a
abc
aba
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, hai đường tạo ra `aba` và `aaa`, đều đối xứng và chứa `a`.

Ở ví dụ 2, đi xuống rồi sang phải hai lần tạo `aaba`, đi phải rồi xuống rồi phải tạo `abba`, đi phải hai lần rồi xuống tạo `abca`. Chỉ `abba` đối xứng.

### Nguồn

Bài tự biên soạn, phiên bản luyện tập trước WGAMEPN — Trò chơi trên bảng chữ, dựa trên `wgamepn.pdf` do người dùng cung cấp.
