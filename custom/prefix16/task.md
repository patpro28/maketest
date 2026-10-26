# PREFIX16 — Đường đi lên xuống

### Đề bài

Có $N$ trạm nằm trên một tuyến đường, trạm thứ $i$ có độ cao $H_i$. Hai trạm liên tiếp được nối bằng một đoạn đường. Đi qua đoạn đường nối trạm $i$ và trạm $i+1$ theo bất kỳ chiều nào đều tốn $|H_{i+1}-H_i|$ đơn vị năng lượng. Mỗi truy vấn gồm hai trạm $L,R$. Hãy tính tổng năng lượng cần để đi theo tuyến đường từ $L$ đến $R$. Nếu $L=R$, năng lượng cần là $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $H_1,H_2,\ldots,H_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng năng lượng cần để đi từ trạm $L$ đến trạm $R$.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $-10^9\le H_i\le10^9$.
- $1\le L,R\le N$.

### Sample Input 1

```text
4 3
2 7 4 4
1 4
3 1
2 2
```

### Sample Output 1

```text
8
8
0
```

### Sample Input 2

```text
1 1
-9
1 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, ba đoạn đường lần lượt tốn $5,3,0$. Đi từ trạm $1$ đến $4$ hoặc từ trạm $3$ về $1$ đều tốn $8$; ở nguyên trạm $2$ không tốn năng lượng. Ở ví dụ 2, chỉ có một trạm nên kết quả là $0$.
