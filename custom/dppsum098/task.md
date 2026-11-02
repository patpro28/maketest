# PREFIX098 — Đếm đoạn có phần dư C với số âm

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, có thể âm, bằng $0$ hoặc dương.

Hãy đếm số đoạn liên tiếp không rỗng có tổng $S$ thỏa $S\equiv C\pmod M$, nghĩa là $S-C$ chia hết cho $M$. Phần dư được chuẩn hóa về khoảng từ $0$ đến $M-1$, kể cả khi tổng âm.

Các đoạn phải nằm hoàn toàn trong dãy, không nối vòng. Các đoạn được phép chồng lấn. Hai đoạn khác nhau nếu có vị trí bắt đầu hoặc vị trí kết thúc khác nhau. Không tính đoạn rỗng.

### Dữ liệu vào

- Dòng đầu chứa 3 số nguyên $N,M,C$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn không rỗng thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$. Không lấy phần dư của đáp án.

### Ràng buộc

- $1\le N\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le M\le200000$.
- $0\le C<M$.

### Sample Input 1

```text
5 3 1
1 -2 3 -1 2
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
3 1 0
0 0 0
```

### Sample Output 2

```text
6
```

### Sample Input 3

```text
1 3 2
1
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, có $6$ đoạn không rỗng thỏa điều kiện. Các cặp đầu mút là $((1,1),(1,4),(2,2),(2,3),(3,5),(4,5))$.

Ở ví dụ 2, có $6$ đoạn không rỗng thỏa điều kiện. Các cặp đầu mút là $((1,1),(1,2),(1,3),(2,2),(2,3),(3,3))$.

Ở ví dụ 3, có $0$ đoạn không rỗng thỏa điều kiện. Không tính đoạn rỗng.
