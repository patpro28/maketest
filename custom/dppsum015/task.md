# PREFIX015 — Tổng các số trong khoảng giá trị

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: $U\le A_i\le V$.

$U,V$ được cho trước và dùng chung cho mọi truy vấn. Hai đầu mút $U,V$ đều được tính.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau đều được cộng vào tổng nếu thỏa điều kiện. Nếu không có phần tử nào thỏa điều kiện, tổng bằng $0$.

Cộng đúng giá trị có dấu của các phần tử được chọn, không lấy trị tuyệt đối.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,Q,U,V$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng giá trị của các phần tử thỏa mãn điều kiện trong đoạn được hỏi.

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
-1
1
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
10
0
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,6]$ có các giá trị thỏa điều kiện là $(-2,0,3,-2)$, được tổng $-1$. Đoạn $[2,4]$ có các giá trị thỏa điều kiện là $(-2,0,3)$, được tổng $1$. Đoạn $[5,5]$ không có phần tử thỏa điều kiện, được tổng $0$.

Ở ví dụ 2: Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(5,5)$, được tổng $10$. Đoạn $[2,2]$ không có phần tử thỏa điều kiện, được tổng $0$.
