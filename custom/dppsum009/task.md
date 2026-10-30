# PREFIX009 — Đếm số chứa chữ số 7

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy đếm số phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: biểu diễn thập phân của $A_i$ chứa ít nhất một chữ số `7`.

Mỗi phần tử thỏa điều kiện chỉ được đếm một lần, kể cả khi chứa nhiều chữ số `7`. Số $0$ không chứa chữ số `7`.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau được đếm riêng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số phần tử thỏa mãn điều kiện trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mỗi truy vấn.

### Sample Input 1

```text
6 3
7 77 17 70 123 0
1 6
2 4
5 6
```

### Sample Output 1

```text
4
3
0
```

### Sample Input 2

```text
3 2
700000007 707 1000000000
1 3
3 3
```

### Sample Output 2

```text
2
0
```

### Giải thích

Ở ví dụ 1, bốn phần tử đầu đều chứa chữ số `7`; $77$ vẫn chỉ được đếm một lần. Đoạn $[5,6]$ không có phần tử thỏa điều kiện. Ở ví dụ 2, $700000007$ và $707$ được tính, còn $1000000000$ không được tính.
