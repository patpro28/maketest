# SEGTREE221 — Mực nước thấp nhất

### Đề bài

Có $n$ hồ chứa nằm dọc theo một con kênh, đánh số từ $1$ đến $n$. Mực nước tại hồ $i$ được biểu diễn bằng số nguyên $a_i$ so với mốc quy ước, nên có thể âm.

Thực hiện lần lượt $q$ thao tác thuộc một trong hai loại.

- `0 l r x` — Cộng $x$ vào mực nước của mỗi hồ trong đoạn $[l,r]$.
- `1 l r` — Hỏi mực nước thấp nhất trong các hồ từ $l$ đến $r$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\ldots,a_n$.
- Trong $q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo định dạng `0 l r x` hoặc `1 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $1$, in một số nguyên là mực nước thấp nhất trong đoạn được hỏi. Mỗi kết quả nằm trên một dòng.

### Ràng buộc

- $1\le n,q\le100000$.
- $-10^9\le a_i\le10^9$ ở thời điểm ban đầu.
- Với mọi thao tác, $1\le l\le r\le n$.
- Với thao tác loại $0$, $-10^9\le x\le10^9$.

### Sample Input 1

```text
5 6
5 -2 3 1 7
1 1 5
0 2 4 4
1 1 4
0 3 5 -6
1 3 5
1 3 3
```

### Sample Output 1

```text
-2
2
-1
1
```

### Sample Input 2

```text
1 6
-1000000000
1 1 1
0 1 1 -1000000000
0 1 1 -1000000000
1 1 1
0 1 1 0
1 1 1
```

### Sample Output 2

```text
-1000000000
-3000000000
-3000000000
```

### Giải thích

Ở ví dụ 1, mực nước thấp nhất ban đầu là $-2$. Sau lần cập nhật đầu tiên, dãy là $[5,2,7,5,7]$ nên đoạn $[1,4]$ có mực nước thấp nhất là $2$. Lần cập nhật tiếp theo cho dãy $[5,2,1,-1,1]$. Hai truy vấn cuối lần lượt nhận $-1$ và $1$.

Ở ví dụ 2, hai lần giảm đưa mực nước của hồ duy nhất xuống $-3\cdot10^9$. Cộng $0$ giữ giá trị này.
