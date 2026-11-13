# DPALL0006 — Thông điệp chung đúng ngân sách

### Đề bài

Cho hai xâu chữ thường $A$ và $B$. Dùng vị trí $i$ của $A$ tốn phí $X_i$, dùng vị trí $j$ của $B$ tốn phí $Y_j$. Mỗi chữ cái $c$ có điểm thưởng $P_c$.

Bạn chọn các cặp vị trí $(i_1,j_1),\ldots,(i_t,j_t)$ sao cho $i_1<\cdots<i_t$, $j_1<\cdots<j_t$ và $A_{i_k}=B_{j_k}$ với mọi $k$. Một cặp $(i,j)$ tốn phí $X_i+Y_j$ và nhận điểm $P_{A_i}$. Có thể không chọn cặp nào, khi đó tổng phí và tổng điểm đều bằng $0$.

Hãy tìm tổng điểm lớn nhất khi tổng phí đúng bằng $S$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,S$, trong đó $N,M$ là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$.
- Dòng thứ ba chứa xâu $B$.
- Dòng thứ tư chứa $N$ số nguyên $X_1,\ldots,X_N$.
- Dòng thứ năm chứa $M$ số nguyên $Y_1,\ldots,Y_M$.
- Dòng thứ sáu chứa $26$ số nguyên $P_a,P_b,\ldots,P_z$ theo thứ tự bảng chữ cái.

### Dữ liệu ra

In tổng điểm lớn nhất nếu có thể đạt đúng phí $S$. Nếu không thể, in $-1$.

### Ràng buộc

- $1\le N,M\le220$; $0\le S\le100$.
- $1\le X_i,Y_j\le100$.
- $0\le P_c\le10^9$.
- $A$ và $B$ chỉ gồm chữ cái thường từ a đến z.

### Sample Input 1

```text
3 3 7
aba
baa
2 1 3
1 2 2
5 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 1

```text
13
```

### Sample Input 2

```text
1 1 1
a
a
1
1
5 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 2

```text
-1
```

### Giải thích

- Ví dụ 1. Ghép chữ b ở cặp $(2,1)$ và chữ a ở cặp $(3,2)$. Tổng phí là $(1+1)+(3+2)=7$, tổng điểm là $8+5=13$. Không thể ghép cả ba chữ vì hai xâu khác nhau.
- Ví dụ 2. Cặp duy nhất tốn phí $2$. Bỏ qua cặp này thì tổng phí là $0$, nên không thể dùng đúng phí $1$.
