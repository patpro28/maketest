# PREFIX016 — Tổng các số chính phương

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $A_i=x^2$ với một số nguyên không âm $x$.

Số $0$ là số chính phương. Các số âm không phải số chính phương.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau đều được cộng vào tổng nếu thỏa điều kiện. Nếu không có phần tử nào thỏa điều kiện, tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng giá trị của các phần tử thỏa mãn điều kiện trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mỗi truy vấn.

### Sample Input 1

```text
7 3
-1 0 1 2 4 9 10
1 7
2 3
4 4
```

### Sample Output 1

```text
14
1
0
```

### Sample Input 2

```text
3 2
999950883 999950884 999950885
1 3
2 2
```

### Sample Output 2

```text
999950884
999950884
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,7]$ có các giá trị thỏa điều kiện là $(0,1,4,9)$, được tổng $14$. Đoạn $[2,3]$ có các giá trị thỏa điều kiện là $(0,1)$, được tổng $1$. Đoạn $[4,4]$ không có phần tử thỏa điều kiện, được tổng $0$.

Ở ví dụ 2: Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(999950884)$, được tổng $999950884$. Đoạn $[2,2]$ có các giá trị thỏa điều kiện là $(999950884)$, được tổng $999950884$.
