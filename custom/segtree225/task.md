# SEGTREE225 — Tải lớn nhất trên vành đai

### Đề bài

Có $n$ trạm nằm trên một vành đai theo thứ tự $1,2,\ldots,n,1$. Tải của trạm $i$ là số nguyên $a_i$.

Đoạn vòng từ $l$ đến $r$ đi theo chiều tăng chỉ số và chứa cả hai đầu. Nếu $l>r$, đoạn đi qua trạm $n$ rồi tiếp tục từ trạm $1$. Nếu $l=r$, đoạn chỉ có một trạm.

Thực hiện lần lượt $q$ thao tác thuộc một trong hai loại.

- `0 l r x` — Cộng $x$ vào tải của mỗi trạm trên đoạn vòng từ $l$ đến $r$.
- `1 l r` — Hỏi tải lớn nhất trên đoạn vòng từ $l$ đến $r$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\ldots,a_n$.
- Trong $q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo định dạng `0 l r x` hoặc `1 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $1$, in một số nguyên là tải lớn nhất trên đoạn vòng được hỏi. Mỗi kết quả nằm trên một dòng.

### Ràng buộc

- $1\le n,q\le100000$.
- $-10^9\le a_i\le10^9$ ở thời điểm ban đầu.
- Với mọi thao tác, $1\le l,r\le n$.
- Với thao tác loại $0$, $-10^9\le x\le10^9$.

### Sample Input 1

```text
5 7
2 7 -4 3 1
1 4 2
0 4 1 5
1 5 2
1 2 4
0 2 2 -10
1 2 2
1 5 3
```

### Sample Output 1

```text
7
7
8
-3
7
```

### Sample Input 2

```text
3 6
-8 -5 -6
1 3 2
0 3 1 -1000000000
0 3 1 -1000000000
1 3 1
0 1 3 -1000000000
1 1 3
```

### Sample Output 2

```text
-5
-2000000006
-1000000005
```

### Giải thích

Ở ví dụ 1, truy vấn đầu xét các trạm $4,5,1,2$ và có đáp án $7$. Lần cập nhật đầu cộng $5$ vào các trạm $4,5,1$, cho dãy $[7,7,-4,8,6]$. Hai truy vấn kế tiếp lần lượt trả về $7$ và $8$. Sau khi trừ $10$ ở trạm $2$, truy vấn chỉ xét trạm này có đáp án $-3$. Trên đoạn vòng cuối gồm các trạm $5,1,2,3$, tải lớn nhất là $7$ ở trạm $1$.

Ở ví dụ 2, truy vấn đầu xét cả ba trạm. Hai lần cập nhật tiếp theo chỉ giảm tải của trạm $3$ và trạm $1$. Tải lớn nhất trong hai trạm đó là $-2000000006$ ở trạm $3$. Sau lần cập nhật cuối, trạm $2$ có tải lớn nhất trên toàn vành đai, bằng $-1000000005$.
