# SEGTREE174 — Tuyến đường ít loại hàng

### Đề bài

Cho chuỗi $s$ gồm $N$ chữ cái thường từ `a` đến `z`. Thực hiện các thao tác:

- `1 i c`: thay ký tự tại vị trí $i$ bằng ký tự $c$.
- `2 l K`: tìm vị trí $r$ lớn nhất trong $[l,N]$ sao cho đoạn chuỗi từ $l$ đến $r$ chứa không quá $K$ loại ký tự khác nhau.

Mỗi ký tự chỉ được tính một loại dù xuất hiện nhiều lần. Chỉ số trong chuỗi được đánh từ $1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa chuỗi $s$ gồm đúng $N$ ký tự.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $s_i,c\in\{\texttt{a},\ldots,\texttt{z}\}$.
- $1\le i,l\le N$; $1\le K\le26$.

### Sample Input 1

```text
7 5
abacaba
2 1 2
2 2 1
1 4 a
2 1 2
2 4 1
```

### Sample Output 1

```text
3
2
7
5
```

### Sample Input 2

```text
1 3
z
2 1 1
1 1 a
2 1 26
```

### Sample Output 2

```text
1
1
```

### Giải thích

Ở ví dụ 1, đoạn `aba` từ vị trí $1$ đến $3$ có hai loại ký tự; thêm `c` sẽ vượt giới hạn. Sau khi thay ký tự thứ $4$ bằng `a`, toàn chuỗi chỉ còn hai loại. Đoạn dài nhất bắt đầu tại $4$ chỉ có một loại là đoạn $[4,5]$. Ở ví dụ 2, mọi truy vấn đều nhận được ký tự duy nhất.
