# PREFIX020 — Tổng các số chứa chữ số 7

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$.

Với mỗi truy vấn, hãy tính tổng giá trị của các phần tử trong đoạn từ vị trí $L$ đến vị trí $R$, tính cả hai đầu mút, thỏa mãn điều kiện: biểu diễn thập phân của $A_i$ chứa ít nhất một chữ số `7`.

Mỗi phần tử thỏa điều kiện chỉ được cộng một lần, kể cả khi chứa nhiều chữ số `7`. Số $0$ không chứa chữ số `7`.

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
6 3
7 77 17 70 123 0
1 6
2 4
5 6
```

### Sample Output 1

```text
171
164
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
700000714
0
```

### Giải thích

Ở ví dụ 1: Đoạn $[1,6]$ có các giá trị thỏa điều kiện là $(7,77,17,70)$, được tổng $171$. Đoạn $[2,4]$ có các giá trị thỏa điều kiện là $(77,17,70)$, được tổng $164$. Đoạn $[5,6]$ không có phần tử thỏa điều kiện, được tổng $0$.

Ở ví dụ 2: Đoạn $[1,3]$ có các giá trị thỏa điều kiện là $(700000007,707)$, được tổng $700000714$. Đoạn $[3,3]$ không có phần tử thỏa điều kiện, được tổng $0$.
