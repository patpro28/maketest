# PREFIX018 — Tổng các số đối xứng

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: biểu diễn thập phân của $A_i$ đọc từ trái sang phải và từ phải sang trái giống nhau.

Không thêm chữ số $0$ ở đầu biểu diễn. Số $0$ và mọi số có một chữ số đều là số đối xứng.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau đều được cộng vào tổng nếu thỏa điều kiện. Nếu không có phần tử nào thỏa điều kiện, tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng giá trị của các phần tử thỏa mãn điều kiện trong đoạn được hỏi.

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
1349
1342
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
1012
0
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,7]$ có các giá trị thỏa điều kiện là $(0,7,121,1221)$, được tổng $1349$. Đoạn $[3,6]$ có các giá trị thỏa điều kiện là $(121,1221)$, được tổng $1342$. Đoạn $[7,7]$ không có phần tử thỏa điều kiện, được tổng $0$.

Ở ví dụ 2: Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(11,1001)$, được tổng $1012$. Đoạn $[3,3]$ không có phần tử thỏa điều kiện, được tổng $0$.
