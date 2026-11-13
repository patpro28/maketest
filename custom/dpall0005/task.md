# DPALL0005 — Kho vật tư hai nguồn

### Đề bài

Kho có $N$ dòng vật tư. Dòng $i$ mô tả vật tư có khối lượng $W_i$, giá trị $V_i$ và loại nguồn $T_i$. Nếu $T_i=0$, chỉ có một món ở dòng đó. Nếu $T_i=1$, số lượng món ở dòng đó không giới hạn.

Hãy chọn vật tư có tổng khối lượng đúng $W$ và tổng giá trị lớn nhất. Hai phương án khác nhau nếu số lượng lấy ở ít nhất một dòng khác nhau. Các dòng khác nhau là các nguồn riêng, kể cả khi thông số giống nhau. Thứ tự lấy các món không tạo thêm phương án.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,W$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $T_i,W_i,V_i$.

### Dữ liệu ra

Nếu có thể đạt đúng khối lượng $W$, in tổng giá trị lớn nhất và số phương án đạt giá trị đó modulo $10^9+7$. Nếu không thể, in $-1$ và $0$.

### Ràng buộc

- $1\le N\le200$; $0\le W\le10000$.
- $T_i\in\{0,1\}$; $1\le W_i\le10000$; $0\le V_i\le10^9$.

### Sample Input 1

```text
3 6
0 2 3
1 2 3
1 3 4
```

### Sample Output 1

```text
9 2
```

### Sample Input 2

```text
2 7
0 2 8
1 4 7
```

### Sample Output 2

```text
-1 0
```

### Giải thích

- Ví dụ 1. Có hai phương án đạt giá trị $9$. Lấy ba món từ dòng thứ hai, hoặc lấy một món từ dòng thứ nhất và hai món từ dòng thứ hai. Lấy hai món từ dòng thứ ba chỉ đạt giá trị $8$.
- Ví dụ 2. Mọi khối lượng đạt được đều chẵn, nên không thể đạt đúng $7$.
