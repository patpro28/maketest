# SEGTREE223 — Kho có số dư thấp nhất

### Đề bài

Có $n$ kho hàng đánh số từ $1$ đến $n$. Số dư tại kho $i$ là số nguyên $a_i$. Số dư âm biểu thị lượng hàng kho đang nợ.

Thực hiện lần lượt $q$ thao tác thuộc một trong hai loại.

- `0 l r x` — Cộng $x$ vào số dư của mỗi kho trong đoạn $[l,r]$.
- `1 l r` — Hỏi số dư nhỏ nhất trong đoạn $[l,r]$ và chỉ số nhỏ nhất trong các kho có số dư bằng giá trị đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\ldots,a_n$.
- Trong $q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo định dạng `0 l r x` hoặc `1 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $1$, in hai số nguyên cách nhau bởi một dấu cách, theo thứ tự là số dư nhỏ nhất và chỉ số nhỏ nhất của kho có số dư đó. Mỗi kết quả nằm trên một dòng.

### Ràng buộc

- $1\le n,q\le100000$.
- $-10^9\le a_i\le10^9$ ở thời điểm ban đầu.
- Với mọi thao tác, $1\le l\le r\le n$.
- Với thao tác loại $0$, $-10^9\le x\le10^9$.

### Sample Input 1

```text
5 6
4 -2 6 -2 1
1 1 5
0 1 3 3
1 2 5
0 4 5 3
1 1 5
1 3 5
```

### Sample Output 1

```text
-2 2
-2 4
1 2
1 4
```

### Sample Input 2

```text
3 6
-1000000000 -1000000000 -1000000000
1 2 3
0 3 3 -1000000000
0 3 3 -1000000000
1 2 3
0 1 3 1000000000
1 1 2
```

### Sample Output 2

```text
-1000000000 2
-3000000000 3
0 1
```

### Giải thích

Ở ví dụ 1, ban đầu các kho $2$ và $4$ cùng có số dư nhỏ nhất $-2$, nên chọn kho $2$. Sau lần cập nhật đầu tiên, kho $4$ có số dư thấp nhất trong đoạn $[2,5]$. Sau lần cập nhật thứ hai, dãy số dư là $[7,1,9,1,4]$. Kho $2$ được chọn trên toàn dãy, còn kho $4$ được chọn trên đoạn $[3,5]$.

Ở ví dụ 2, hai kho trong truy vấn đầu có cùng số dư nên chọn kho $2$. Hai lần cập nhật giảm số dư của kho $3$ xuống $-3\cdot10^9$, do đó truy vấn thứ hai chọn kho $3$. Lần cập nhật cuối đưa số dư của hai kho đầu về $0$, nên truy vấn cuối chọn kho $1$.
