# PREFIX011 — Tổng các số chẵn

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $A_i$ là số chẵn.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau đều được cộng vào tổng nếu thỏa điều kiện. Nếu không có phần tử nào thỏa điều kiện, tổng bằng $0$.

Số $0$ và số âm chia hết cho $2$ cũng là số chẵn.

Cộng đúng giá trị có dấu của các phần tử được chọn, không lấy trị tuyệt đối.

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
6 3
-2 0 3 8 -4 5
1 6
1 3
3 3
```

### Sample Output 1

```text
2
-2
0
```

### Sample Input 2

```text
3 2
1000000000 1000000000 -2
1 3
1 2
```

### Sample Output 2

```text
1999999998
2000000000
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,6]$ có các giá trị thỏa điều kiện là $(-2,0,8,-4)$, được tổng $2$. Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(-2,0)$, được tổng $-2$. Đoạn $[3,3]$ không có phần tử thỏa điều kiện, được tổng $0$.

Ở ví dụ 2: Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(1000000000,1000000000,-2)$, được tổng $1999999998$. Đoạn $[1,2]$ có các giá trị thỏa điều kiện là $(1000000000,1000000000)$, được tổng $2000000000$.
