# SEGTREE222 — Biên độ nhiệt

### Đề bài

Có $n$ trạm đo nhiệt độ trên một tuyến đường, đánh số từ $1$ đến $n$. Nhiệt độ đo được tại trạm $i$ là số nguyên $a_i$. Biên độ nhiệt của một đoạn là hiệu giữa nhiệt độ cao nhất và nhiệt độ thấp nhất trong đoạn đó.

Thực hiện lần lượt $q$ thao tác thuộc một trong hai loại.

- `0 l r x` — Cộng $x$ vào nhiệt độ tại mỗi trạm trong đoạn $[l,r]$.
- `1 l r` — Hỏi biên độ nhiệt trên đoạn $[l,r]$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\ldots,a_n$.
- Trong $q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo định dạng `0 l r x` hoặc `1 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $1$, in một số nguyên là biên độ nhiệt của đoạn được hỏi. Mỗi kết quả nằm trên một dòng.

### Ràng buộc

- $1\le n,q\le100000$.
- $-10^9\le a_i\le10^9$ ở thời điểm ban đầu.
- Với mọi thao tác, $1\le l\le r\le n$.
- Với thao tác loại $0$, $-10^9\le x\le10^9$.

### Sample Input 1

```text
5 6
4 7 -1 7 2
1 1 5
0 2 4 3
1 2 5
0 1 5 -5
1 1 2
1 4 4
```

### Sample Output 1

```text
8
8
6
0
```

### Sample Input 2

```text
2 6
-1000000000 1000000000
1 1 2
0 1 1 -1000000000
1 1 2
0 2 2 1000000000
1 1 2
1 2 2
```

### Sample Output 2

```text
2000000000
3000000000
4000000000
0
```

### Giải thích

Ở ví dụ 1, biên độ nhiệt ban đầu là $7-(-1)=8$. Sau lần cập nhật đầu tiên, đoạn $[2,5]$ chứa các giá trị $10,2,10,2$ nên biên độ vẫn bằng $8$. Sau khi giảm nhiệt độ ở cả năm trạm đi $5$, đoạn $[1,2]$ có hai giá trị $-1,5$ nên biên độ bằng $6$. Đoạn chỉ có một trạm có biên độ bằng $0$.

Ở ví dụ 2, hai nhiệt độ ban đầu là $-10^9$ và $10^9$. Hai lần cập nhật lần lượt hạ nhiệt độ ở trạm thứ nhất xuống $-2\cdot10^9$ và nâng nhiệt độ ở trạm thứ hai lên $2\cdot10^9$. Biên độ của cả đoạn tăng từ $2\cdot10^9$ lên $3\cdot10^9$, rồi lên $4\cdot10^9$.
