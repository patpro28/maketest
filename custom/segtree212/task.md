# SEGTREE212 — Hai dãy bàn

### Đề bài

Có $N$ bàn xếp thành hàng. Bàn $i$ có điểm $A_i$. Các bàn có chỉ số lẻ thuộc nhóm thứ nhất và các bàn có chỉ số chẵn thuộc nhóm thứ hai.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ điểm cho từng bàn trong đoạn $[L,R]$.
- `2 L R`. In hai số theo thứ tự là tổng điểm các bàn có chỉ số lẻ và tổng điểm các bàn có chỉ số chẵn trong đoạn $[L,R]$. Tổng của nhóm rỗng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác. Hai số trên cùng một dòng cách nhau bởi một dấu cách.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10^8$ ở đầu vào.

### Sample Input 1

```text
5 4
1 2 3 4 5
2 2 5
1 2 4 10
2 2 5
2 4 4
```

### Sample Output 1

```text
8 6
18 26
0 14
```

### Sample Input 2

```text
3 3
2 -2 2
1 1 3 -3
2 1 3
2 3 3
```

### Sample Output 2

```text
-2 -5
-1 0
```

### Giải thích

Ở ví dụ 1, ban đầu đoạn $[2,5]$ có tổng lẻ $3+5=8$ và tổng chẵn $2+4=6$. Lần cộng làm nhóm lẻ tăng $10$ và nhóm chẵn tăng $20$. Bàn $4$ có điểm $14$ và thuộc nhóm chẵn.

Ở ví dụ 2, dãy sau cập nhật là $[-1,-5,-1]$. Hai bàn lẻ có tổng $-2$, còn bàn chẵn có điểm $-5$.
