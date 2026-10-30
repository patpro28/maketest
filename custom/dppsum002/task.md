# PREFIX002 — Đếm số âm

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy đếm số phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $A_i<0$.

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
6 3
-2 0 3 -5 -1 4
1 6
2 3
4 5
```

### Sample Output 1

```text
3
0
2
```

### Sample Input 2

```text
1 1
0
1 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, các số âm của cả dãy là $-2,-5,-1$; đoạn $[2,3]$ không có số âm; đoạn $[4,5]$ có hai số âm. Ở ví dụ 2, số $0$ không được tính.
