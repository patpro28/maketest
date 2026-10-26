# SEGTREE025 — Bậc thang cao nhất

### Đề bài

Một lối đi có $N$ vị trí liên tiếp, được đánh số từ $1$ đến $N$. Độ cao tại vị trí $i$ là số nguyên $A_i$. Độ cao có thể âm so với mốc quy ước.

Bậc giữa hai vị trí kề nhau $i,i+1$ có độ chênh lệch $|A_{i+1}-A_i|$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: sửa độ cao $A_i$ thành $x$.
- `2 l r`: tìm độ chênh lệch lớn nhất của một bậc nằm hoàn toàn trong đoạn $[l,r]$.

Nếu $l=r$, đoạn không có bậc nào và đáp án được quy ước bằng $0$. Chỉ xét các cặp vị trí kề nhau cùng nằm trong đoạn được hỏi. Mỗi truy vấn sử dụng các độ cao sau tất cả thao tác sửa trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả độ cao ban đầu tại các vị trí.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa độ chênh lệch lớn nhất giữa hai vị trí kề nhau trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
5 7
2 8 5 5 -1
2 1 5
2 2 4
2 4 4
1 3 -4
2 2 4
1 2 -4
2 1 3
```

### Sample Output 1

```text
6
3
0
12
6
```

### Sample Input 2

```text
2 4
-1000000000 1000000000
2 1 2
1 1 1000000000
2 1 2
2 2 2
```

### Sample Output 2

```text
2000000000
0
0
```

### Giải thích

Ở ví dụ 1, các chênh lệch ban đầu là $6,3,0,6$, nên truy vấn cả lối đi có đáp án $6$. Đoạn $[2,4]$ chỉ có hai chênh lệch $3,0$, còn đoạn một vị trí trả về $0$. Sửa độ cao vị trí $3$ thành $-4$ làm hai chênh lệch kề vị trí này thành $12,9$, nên đoạn $[2,4]$ trả về $12$. Sau khi sửa vị trí $2$ thành $-4$, đoạn $[1,3]$ có các chênh lệch $6,0$, đáp án là $6$.

Ở ví dụ 2, chênh lệch ban đầu là $2\cdot10^9$. Khi hai độ cao bằng nhau, bậc giữa chúng có chênh lệch $0$.
