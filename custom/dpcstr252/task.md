# DPCSTR252 — Khôi phục bản tin có điểm

### Đề bài

Cho hai xâu chữ thường $A,B$, số nguyên $K$, mức phạt $Q$ và điểm $W_c$ của mỗi chữ cái. Điểm $W_c$ có thể âm.

Chọn hai đoạn con liên tiếp có cùng độ dài, mỗi đoạn trong một xâu, sao cho có không quá $K$ cặp ký tự khác nhau ở các vị trí tương ứng. Cặp hai ký tự bằng nhau và cùng là chữ $c$ nhận $W_c$ điểm; cặp khác nhau nhận $-Q$ điểm. Tổng điểm bằng tổng điểm của mọi cặp, không được bỏ qua cặp nằm bên trong hai đoạn.

Hãy tìm tổng điểm lớn nhất. Được phép chọn hai đoạn rỗng có điểm $0$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,M,K,Q$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa $26$ số nguyên $W_a,W_b,\ldots,W_z$ theo thứ tự từ `a` đến `z`.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N,M\le2500$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le K\le5$.
- $-10^9\le W_c\le10^9$ với mọi chữ cái $c$.
- $0\le Q\le10^9$.

### Sample Input 1

```text
4 4 1 2
abcd
abxd
3 4 9 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
2 2 0 2
aa
bb
1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, chọn cả hai xâu được $3+4-2+5=10$ điểm; chỉ có một cặp khác nhau là `c` và `x`. Ở ví dụ 2, không được phép chọn cặp khác nhau, nên chỉ có thể chọn hai đoạn rỗng.
