# PREFIX007 — Đếm số đối xứng

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy đếm số phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: biểu diễn thập phân của $A_i$ đọc từ trái sang phải và từ phải sang trái giống nhau.

Không thêm chữ số $0$ ở đầu biểu diễn. Số $0$ và mọi số có một chữ số đều là số đối xứng.

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
7 3
0 7 10 121 1221 123 1000000000
1 7
3 6
7 7
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
11 1001 1010
1 3
3 3
```

### Sample Output 2

```text
2
0
```

### Giải thích

Ở ví dụ 1, các số đối xứng là $0,7,121,1221$; đoạn $[3,6]$ có hai số đối xứng; $1000000000$ không đối xứng. Ở ví dụ 2, $11,1001$ đối xứng còn $1010$ không đối xứng.
