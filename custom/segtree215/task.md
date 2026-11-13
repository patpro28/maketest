# SEGTREE215 — Tổng theo môđun

### Đề bài

Cho dãy $A_1,\dots,A_N$ và môđun dương $M$. Các phép cộng được hiểu trên số nguyên. Mỗi lần hỏi tổng, bạn chỉ cần trả về số dư theo môđun $M$.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào từng phần tử trong đoạn $[L,R]$.
- `2 L R`. In số dư thuộc $[0,M-1]$ của tổng $\sum_{i=L}^{R}A_i$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10^9$ ở đầu vào.
- $1\le M\le10^9$.

### Sample Input 1

```text
4 4 7
6 -2 5 0
2 1 3
1 2 4 -4
2 2 4
2 1 4
```

### Sample Output 1

```text
2
5
4
```

### Sample Input 2

```text
1 3 1
1000000000
2 1 1
1 1 1 -1000000000
2 1 1
```

### Sample Output 2

```text
0
0
```

### Giải thích

Ở ví dụ 1, tổng đầu tiên là $9$, cho số dư $2$. Sau cập nhật, dãy là $[6,-6,1,-4]$. Hai tổng còn lại là $-9$ và $-3$, có số dư không âm là $5$ và $4$.

Ở ví dụ 2, môđun bằng $1$ nên cả hai câu trả lời đều bằng $0$.
