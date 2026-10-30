# PREFIX005 — Đếm số chính phương

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy đếm số phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $A_i=x^2$ với một số nguyên không âm $x$.

Số $0$ là số chính phương. Các số âm không phải số chính phương.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số phần tử thỏa mãn điều kiện trong đoạn được hỏi.

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
4
2
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
1
1
```

### Giải thích

Ở ví dụ 1, các số chính phương là $0,1,4,9$; đoạn $[2,3]$ có hai số chính phương; số $2$ không phải số chính phương. Ở ví dụ 2, chỉ có $999950884=31622^2$ là số chính phương.
