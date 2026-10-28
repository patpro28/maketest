# SEGTREE114 — Tiền tố chung của hai bản ghi

### Đề bài

Có hai chuỗi $s$ và $t$ cùng độ dài $N$, gồm các chữ cái thường từ `a` đến `z`. Thực hiện các thao tác:

- `1 b i c`: thay ký tự ở vị trí $i$ bằng $c$ trong chuỗi thứ $b$; $b=1$ là chuỗi $s$, $b=2$ là chuỗi $t$.
- `2`: in độ dài tiền tố chung dài nhất của hai chuỗi hiện tại.

Tiền tố chung dài nhất là số $L$ lớn nhất trong $[0,N]$ sao cho $s_i=t_i$ với mọi $1\le i\le L$. Nếu ký tự đầu tiên đã khác nhau, đáp án là $0$. Nếu hai chuỗi giống hệt nhau, đáp án là $N$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa chuỗi $s$ gồm đúng $N$ ký tự.
- Dòng thứ ba chứa chuỗi $t$ gồm đúng $N$ ký tự.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $b\in\{1,2\}$; $1\le i\le N$.
- $s_i,t_i,c\in\{\texttt{a},\ldots,\texttt{z}\}$.

### Sample Input 1

```text
5 7
abcde
abzde
2
1 2 3 c
2
1 1 1 z
2
1 2 1 z
2
```

### Sample Output 1

```text
2
5
0
5
```

### Sample Input 2

```text
1 4
a
b
2
1 1 1 b
2
1 2 1 a
```

### Sample Output 2

```text
0
1
```

### Giải thích

Ở ví dụ 1, hai chuỗi ban đầu chung tiền tố `ab`, dài $2$. Sửa ký tự thứ $3$ của chuỗi thứ hai làm hai chuỗi giống nhau. Thay ký tự đầu của chuỗi thứ nhất tạo khác biệt ngay đầu, nên đáp án bằng $0$. Sửa tiếp ký tự đầu chuỗi thứ hai đưa đáp án trở lại $5$. Ở ví dụ 2, hai truy vấn có kết quả $0$ rồi $1$.
