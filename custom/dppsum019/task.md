# PREFIX019 — Tổng các số có tổng chữ số bằng K

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: tổng các chữ số thập phân của $A_i$ bằng $K$.

$K$ được cho trước và dùng chung cho mọi truy vấn. Tổng chữ số của $0$ bằng $0$.

Các phần tử có giá trị bằng nhau ở những vị trí khác nhau đều được cộng vào tổng nếu thỏa điều kiện. Nếu không có phần tử nào thỏa điều kiện, tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng giá trị của các phần tử thỏa mãn điều kiện trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- $1\le L\le R\le N$ trong mỗi truy vấn.
- $0\le K\le81$.

### Sample Input 1

```text
6 3 10
19 28 100 55 0 91
1 6
3 5
2 4
```

### Sample Output 1

```text
193
55
83
```

### Sample Input 2

```text
4 2 0
0 10 0 1
1 4
2 2
```

### Sample Output 2

```text
0
0
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,6]$ có các giá trị thỏa điều kiện là $(19,28,55,91)$, được tổng $193$. Đoạn $[3,5]$ có các giá trị thỏa điều kiện là $(55)$, được tổng $55$. Đoạn $[2,4]$ có các giá trị thỏa điều kiện là $(28,55)$, được tổng $83$.

Ở ví dụ 2: Đoạn $[1,4]$ có các giá trị thỏa điều kiện là $(0,0)$, được tổng $0$. Đoạn $[2,2]$ không có phần tử thỏa điều kiện, được tổng $0$.
