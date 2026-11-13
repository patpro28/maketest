# DPSTR230 — Đoạn tin giá trị

### Đề bài

Cho hai xâu chữ thường $A,B$ và điểm $W_c$ của mỗi chữ cái từ `a` đến `z`. Điểm có thể âm, bằng $0$ hoặc dương. Điểm của một đoạn bằng tổng điểm của các ký tự trong đoạn, tính từng lần xuất hiện.

Hãy tìm điểm lớn nhất của một đoạn con liên tiếp chung của hai xâu. Được phép chọn đoạn rỗng có điểm $0$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa $26$ số nguyên $W_a,W_b,\ldots,W_z$ theo thứ tự từ `a` đến `z`.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N,M\le5000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.
- $-10^9\le W_c\le10^9$ với mọi chữ cái $c$.

### Sample Input 1

```text
4 6
abca
zabcaz
5 -20 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 1

```text
12
```

### Sample Input 2

```text
3 2
aaa
aa
-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, chọn `ca`, có điểm $7+5=12$. Đoạn chung dài hơn `abca` có điểm âm nên không tối ưu. Ở ví dụ 2, mọi đoạn không rỗng đều có điểm âm, nên chọn đoạn rỗng.
