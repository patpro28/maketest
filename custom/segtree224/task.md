# SEGTREE224 — Số người đạt điểm cao nhất

### Đề bài

Có $n$ thí sinh được đánh số từ $1$ đến $n$. Điểm hiện tại của thí sinh $i$ là số nguyên $a_i$. Ban tổ chức có thể điều chỉnh đồng loạt điểm của các thí sinh trong một đoạn.

Thực hiện lần lượt $q$ thao tác thuộc một trong hai loại.

- `0 l r x` — Cộng $x$ vào điểm của mỗi thí sinh trong đoạn $[l,r]$.
- `1 l r` — Hỏi điểm cao nhất trong đoạn $[l,r]$ và số thí sinh trong đoạn đạt điểm đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\ldots,a_n$.
- Trong $q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo định dạng `0 l r x` hoặc `1 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $1$, in hai số nguyên cách nhau bởi một dấu cách, theo thứ tự là điểm cao nhất và số thí sinh trong đoạn có điểm đó. Mỗi kết quả nằm trên một dòng.

### Ràng buộc

- $1\le n,q\le100000$.
- $-10^9\le a_i\le10^9$ ở thời điểm ban đầu.
- Với mọi thao tác, $1\le l\le r\le n$.
- Với thao tác loại $0$, $-10^9\le x\le10^9$.

### Sample Input 1

```text
5 6
3 5 5 1 3
1 1 5
0 4 5 2
1 2 5
0 2 3 -4
1 1 4
1 4 5
```

### Sample Output 1

```text
5 2
5 3
3 2
5 1
```

### Sample Input 2

```text
2 6
-1000000000 -1000000000
0 1 2 -1000000000
0 1 2 -1000000000
1 1 2
0 1 1 1000000000
1 1 2
1 2 2
```

### Sample Output 2

```text
-3000000000 2
-2000000000 1
-3000000000 1
```

### Giải thích

Ở ví dụ 1, ban đầu hai thí sinh đạt điểm cao nhất $5$. Sau khi tăng điểm của thí sinh $4$ và $5$, có ba người trong đoạn $[2,5]$ đạt $5$. Lần cập nhật tiếp theo cho dãy $[3,1,1,3,5]$. Đoạn $[1,4]$ có hai người đạt $3$, còn đoạn $[4,5]$ có một người đạt $5$.

Ở ví dụ 2, sau hai lần giảm điểm, cả hai thí sinh cùng có $-3\cdot10^9$ điểm. Sau khi tăng điểm cho thí sinh $1$, chỉ người đó đạt $-2\cdot10^9$. Truy vấn cuối chỉ xét thí sinh $2$.
