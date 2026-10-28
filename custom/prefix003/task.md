# PREFIX003 — Đếm số chia hết

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy đếm số phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $A_i$ chia hết cho $K$.

$K$ là một số nguyên dương cho trước và dùng chung cho mọi truy vấn. Số $0$ chia hết cho mọi $K$ nguyên dương.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số phần tử thỏa mãn điều kiện trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mỗi truy vấn.
- $1\le K\le10^9$.

### Sample Input 1

```text
6 3 3
-6 0 5 9 -4 12
1 6
2 4
3 3
```

### Sample Output 1

```text
4
2
0
```

### Sample Input 2

```text
3 2 1
-1 0 2
1 3
2 2
```

### Sample Output 2

```text
3
1
```

### Giải thích

Ở ví dụ 1, bốn phần tử $-6,0,9,12$ chia hết cho $3$; đoạn $[2,4]$ có $0,9$; số $5$ không chia hết cho $3$. Ở ví dụ 2, mọi số nguyên đều chia hết cho $1$.
