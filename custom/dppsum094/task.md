# PREFIX094 — Đếm đoạn có tổng T và đủ dài

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, có thể âm, bằng $0$ hoặc dương.

Hãy đếm số đoạn liên tiếp không rỗng có tổng bằng $T$ và có độ dài ít nhất $K$.

Các đoạn phải nằm hoàn toàn trong dãy, không nối vòng. Các đoạn được phép chồng lấn. Hai đoạn khác nhau nếu có vị trí bắt đầu hoặc vị trí kết thúc khác nhau. Không tính đoạn rỗng.

### Dữ liệu vào

- Dòng đầu chứa 3 số nguyên $N,T,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn không rỗng thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$. Không lấy phần dư của đáp án.

### Ràng buộc

- $1\le N\le200000$.
- $-10^9\le A_i\le10^9$.
- $-2\cdot10^{14}\le T\le2\cdot10^{14}$.
- $1\le K\le N$.

### Sample Input 1

```text
5 0 2
1 -1 2 -2 0
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
3 0 2
0 0 0
```

### Sample Output 2

```text
3
```

### Sample Input 3

```text
2 0 2
1 2
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, có $5$ đoạn không rỗng thỏa điều kiện. Các cặp đầu mút là $((1,2),(1,4),(1,5),(3,4),(3,5))$.

Ở ví dụ 2, có $3$ đoạn không rỗng thỏa điều kiện. Các cặp đầu mút là $((1,2),(1,3),(2,3))$.

Ở ví dụ 3, có $0$ đoạn không rỗng thỏa điều kiện. Không tính đoạn rỗng.
