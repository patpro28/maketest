# DPTREE27 — Không chọn ba người liên tiếp

### Đề bài

Cho một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$, có gốc là đỉnh $1$. Đỉnh $i$ có giá trị $A_i$, có thể âm.

Bạn muốn chọn một tập đỉnh sao cho trên mọi đường đi **từ gốc đến một lá**, không có ba đỉnh liên tiếp nào cùng được chọn. Lá là đỉnh không có con trong cây đã chọn gốc.

Hãy tìm tổng giá trị lớn nhất của các đỉnh được chọn. Được phép chọn tập rỗng, khi đó tổng giá trị bằng $0$.

Điều kiện chỉ áp dụng cho những đường đi từ gốc đến lá. Ba đỉnh nằm trên một đường đi qua hai nhánh khác nhau không bị cấm chỉ vì chúng cùng được chọn.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây.

### Dữ liệu ra

In một số nguyên là tổng giá trị lớn nhất của một tập đỉnh hợp lệ.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $-10^9\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây.

### Sample Input 1

```text
4
5 6 7 8
1 2
2 3
3 4
```

### Sample Output 1

```text
20
```

### Sample Input 2

```text
3
5 6 7
1 2
1 3
```

### Sample Output 2

```text
18
```

### Giải thích

Ở ví dụ 1, chọn các đỉnh $1,3,4$ có tổng giá trị $5+7+8=20$. Trên đường từ gốc đến lá, không có ba đỉnh liên tiếp cùng được chọn. Đây là tổng lớn nhất.

Ở ví dụ 2, có thể chọn cả ba đỉnh. Hai đường từ gốc đến lá là $1\to2$ và $1\to3$, mỗi đường chỉ có hai đỉnh. Tổng giá trị bằng $18$.
