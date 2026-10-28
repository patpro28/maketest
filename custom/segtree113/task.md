# SEGTREE113 — Đỉnh núi đầu tiên

### Đề bài

Cho dãy độ cao $a_1,\ldots,a_N$. Vị trí $i$ là một đỉnh núi nếu $2\le i<N$, $a_i>a_{i-1}$ và $a_i>a_{i+1}$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2`: tìm vị trí nhỏ nhất là đỉnh núi. Nếu không có, in `-1`.

Hai đầu dãy không được tính là đỉnh. Độ cao bằng nhau không tạo thành đỉnh núi tại vị trí đang xét.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le a_i,x\le10^9$; $1\le i\le N$.

### Sample Input 1

```text
6 7
1 4 2 2 5 1
2
1 2 2
2
1 4 6
2
1 3 6
2
```

### Sample Output 1

```text
2
5
4
-1
```

### Sample Input 2

```text
2 3
5 -1
2
1 2 10
2
```

### Sample Output 2

```text
-1
-1
```

### Giải thích

Ở ví dụ 1, các đỉnh ban đầu ở vị trí $2$ và $5$. Sau khi đổi độ cao thứ $2$ thành $2$, đỉnh đầu tiên là $5$. Khi độ cao thứ $4$ thành $6$, đỉnh đầu tiên chuyển tới $4$. Sau cập nhật cuối, hai độ cao $6$ kề nhau nên không còn đỉnh nào. Ở ví dụ 2, cả hai phần tử đều ở đầu dãy nên mọi truy vấn trả về $-1$.
