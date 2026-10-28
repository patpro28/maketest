# CUASOMIN — Tổng cực tiểu trong cửa sổ

### Đề bài

Cho dãy $A_1,A_2,\ldots,A_N$ và $Q$ truy vấn. Mỗi truy vấn gồm hai chỉ số $L,R$.

Với truy vấn này, xét mọi đoạn liên tiếp không rỗng nằm hoàn toàn trong $[L,R]$. Chi phí của một đoạn là phần tử nhỏ nhất trong đoạn đó. Bạn cần tính tổng chi phí:

$$\sum_{L\le i\le j\le R}\min(A_i,A_{i+1},\ldots,A_j).$$

Mỗi đoạn được tính một lần, kể cả các đoạn chỉ có một phần tử. Các giá trị bằng nhau vẫn nằm ở các vị trí khác nhau.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in tổng chi phí cần tìm trên một dòng, theo thứ tự truy vấn trong dữ liệu vào. Không lấy phần dư theo modulo.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $0\le A_i\le10^6$.
- $1\le L\le R\le N$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3 3
3 1 2
1 3
2 3
1 1
```

### Sample Output 1

```text
9
4
3
```

### Sample Input 2

```text
4 3
2 2 2 2
1 4
2 3
4 4
```

### Sample Output 2

```text
20
6
2
```

### Sample Input 3

```text
3 3
0 4 0
1 3
1 2
1 1
```

### Sample Output 3

```text
4
4
0
```

### Giải thích

Ở ví dụ 1, với truy vấn $[1,3]$, các đoạn độ dài $1$ đóng góp $3+1+2=6$, các đoạn độ dài $2$ đóng góp $1+1=2$, đoạn độ dài $3$ đóng góp $1$. Tổng bằng $9$. Trong $[2,3]$, tổng là $1+2+1=4$.

Ở ví dụ 2, mỗi đoạn con có cực tiểu bằng $2$. Cửa sổ độ dài $m$ có $m(m+1)/2$ đoạn, nên ba đáp án là $20,6,2$.

Ở ví dụ 3, chỉ các đoạn gồm riêng phần tử tại vị trí $2$ có cực tiểu khác $0$.
