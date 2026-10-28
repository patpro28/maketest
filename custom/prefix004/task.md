# PREFIX004 — Đếm số trong khoảng giá trị

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy đếm số phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $U\le A_i\le V$.

$U,V$ được cho trước và dùng chung cho mọi truy vấn. Hai đầu mút $U,V$ đều được tính.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,Q,U,V$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số phần tử thỏa mãn điều kiện trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mỗi truy vấn.
- $-10^9\le U\le V\le10^9$.

### Sample Input 1

```text
6 3 -2 3
-3 -2 0 3 4 -2
1 6
2 4
5 5
```

### Sample Output 1

```text
4
3
0
```

### Sample Input 2

```text
3 2 5 5
5 4 5
1 3
2 2
```

### Sample Output 2

```text
2
0
```

### Giải thích

Ở ví dụ 1, các phần tử thuộc khoảng $[-2,3]$ là $-2,0,3,-2$ tại các vị trí $2,3,4,6$. Đoạn $[2,4]$ có ba phần tử thỏa điều kiện, còn đoạn $[5,5]$ không có. Ở ví dụ 2, khoảng chỉ chứa giá trị $5$.
