# PREFIX017 — Tổng các số nguyên tố

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $A_i$ là số nguyên tố.

Số nguyên tố là số nguyên lớn hơn $1$ có đúng hai ước nguyên dương là $1$ và chính nó. Các số $0,1$ không phải số nguyên tố.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau đều được cộng vào tổng nếu thỏa điều kiện. Nếu không có phần tử nào thỏa điều kiện, tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng giá trị của các phần tử thỏa mãn điều kiện trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^6$.
- $1\le L\le R\le N$ trong mỗi truy vấn.

### Sample Input 1

```text
7 3
0 1 2 3 4 17 25
1 7
1 2
3 5
```

### Sample Output 1

```text
22
0
5
```

### Sample Input 2

```text
3 2
999983 1000000 1
1 3
2 3
```

### Sample Output 2

```text
999983
0
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,7]$ có các giá trị thỏa điều kiện là $(2,3,17)$, được tổng $22$. Đoạn $[1,2]$ không có phần tử thỏa điều kiện, được tổng $0$. Đoạn $[3,5]$ có các giá trị thỏa điều kiện là $(2,3)$, được tổng $5$.

Ở ví dụ 2: Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(999983)$, được tổng $999983$. Đoạn $[2,3]$ không có phần tử thỏa điều kiện, được tổng $0$.
