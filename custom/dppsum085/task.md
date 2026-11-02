# PREFIX085 — Đếm đoạn có tổng nhỏ hơn T

### Đề bài

Cho dãy $N$ số nguyên không âm $A_1,A_2,\ldots,A_N$, đánh số từ $1$.

Hãy đếm số đoạn liên tiếp không rỗng có tổng nhỏ hơn $T$. Không tính đoạn có tổng bằng $T$.

Độ dài đoạn được phép thay đổi. Chỉ xét đoạn không rỗng nằm hoàn toàn trong dãy, không nối vòng. Các đoạn được phép chồng lấn; hai đoạn khác nhau nếu có vị trí bắt đầu hoặc vị trí kết thúc khác nhau.

### Dữ liệu vào

- Dòng đầu chứa 2 số nguyên $N,T$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn không rỗng thỏa điều kiện. Nếu không có đoạn nào thỏa điều kiện, in $0$.

### Ràng buộc

- $1\le N\le200000$.
- $0\le A_i\le10^9$.
- $0\le T\le2\cdot10^{14}$.

### Sample Input 1

```text
6 4
2 1 3 1 1 2
```

### Sample Output 1

```text
9
```

### Sample Input 2

```text
3 0
0 0 0
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
2 4
5 6
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1: Có $9$ đoạn không rỗng thỏa điều kiện. Các cặp đầu mút là $((1,1),(1,2),(2,2),(3,3),(4,4),(4,5),(5,5),(5,6),(6,6))$.

Ở ví dụ 2: Có $0$ đoạn không rỗng thỏa điều kiện. Không đếm đoạn rỗng.

Ở ví dụ 3: Có $0$ đoạn không rỗng thỏa điều kiện. Không đếm đoạn rỗng.
