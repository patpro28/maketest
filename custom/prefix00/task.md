# PREFIX00 — Kho hàng theo ngày

### Đề bài

Có $N$ ngày nhập hàng. Ngày thứ $i$, kho nhận thêm $A_i$ đơn vị hàng. Có $Q$ truy vấn, mỗi truy vấn gồm hai chỉ số $L,R$. Hãy tính tổng lượng hàng nhập từ ngày $L$ đến ngày $R$, tính cả hai ngày.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng lượng hàng nhập trong khoảng được hỏi.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$; $1\le L\le R\le N$ trong mỗi truy vấn.
- $0\le A_i\le10^9$.

### Sample Input 1

```text
5 3
3 0 7 2 5
1 3
2 5
4 4
```

### Sample Output 1

```text
10
14
2
```

### Sample Input 2

```text
1 2
1000000000
1 1
1 1
```

### Sample Output 2

```text
1000000000
1000000000
```

### Giải thích

Ở ví dụ 1, ba tổng lần lượt là $3+0+7=10$, $0+7+2+5=14$ và $2$. Ở ví dụ 2, cả hai truy vấn đều hỏi lượng hàng của ngày duy nhất.
