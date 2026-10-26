# SEGTREE032 — Nhịp chênh lệch

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Với một đoạn $[l,r]$ có ít nhất hai phần tử, **nhịp chênh lệch** là ước chung lớn nhất (GCD) của các số $|A_{l+1}-A_l|,|A_{l+2}-A_{l+1}|,\ldots,|A_r-A_{r-1}|$.

Quy ước nhịp chênh lệch bằng $0$ nếu đoạn chỉ có một phần tử hoặc mọi chênh lệch trong đoạn đều bằng $0$. Các chênh lệch bằng $0$ còn lại không ảnh hưởng đến GCD; chẳng hạn $\gcd(0,6)=6$.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: tính nhịp chênh lệch của đoạn $[l,r]$.

Chỉ xét các cặp phần tử kề nhau cùng nằm trong đoạn được hỏi. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa nhịp chênh lệch của đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
5 7
6 10 14 22 22
2 1 5
2 4 5
2 3 3
1 3 13
2 1 4
1 2 6
2 1 3
```

### Sample Output 1

```text
4
0
0
1
7
```

### Sample Input 2

```text
1 3
-1000000000
2 1 1
1 1 1000000000
2 1 1
```

### Sample Output 2

```text
0
0
```

### Giải thích

Ở ví dụ 1, các chênh lệch ban đầu là $4,4,8,0$, có GCD bằng $4$. Hai phần tử ở vị trí $4,5$ bằng nhau nên nhịp chênh lệch của đoạn đó bằng $0$. Đoạn chỉ có phần tử $3$ cũng trả về $0$. Sau khi gán $A_3=13$, đoạn $[1,4]$ có các chênh lệch $4,3,9$, GCD bằng $1$. Khi gán tiếp $A_2=6$, đoạn $[1,3]$ có các chênh lệch $0,7$, GCD bằng $7$.

Ở ví dụ 2, dãy chỉ có một phần tử nên mọi truy vấn đều trả về $0$, dù giá trị phần tử thay đổi.
