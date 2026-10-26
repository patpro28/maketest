# SEGTREE001 — Độ cao địa hình

### Đề bài

Một đoạn đường có $N$ điểm đo được đánh số từ $1$ đến $N$. Độ cao tại điểm $i$ là số nguyên $A_i$; độ cao có thể âm so với mốc quy ước.

Bạn cần trả lời $Q$ truy vấn. Với mỗi đoạn $[l,r]$, hãy tìm độ cao thấp nhất, độ cao cao nhất và độ chênh lệch giữa hai độ cao này trong các điểm từ $l$ đến $r$.

Độ cao tại các điểm được giữ nguyên trong suốt quá trình trả lời truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả độ cao tại từng điểm.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $l,r$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng gồm ba số nguyên theo thứ tự: độ cao thấp nhất, độ cao cao nhất và độ chênh lệch trên đoạn được hỏi. Các số cách nhau một dấu cách.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le l\le r\le N$.

### Sample Input 1

```text
6 4
5 -2 7 7 0 -2
1 6
3 4
2 5
6 6
```

### Sample Output 1

```text
-2 7 9
7 7 0
-2 7 9
-2 -2 0
```

### Sample Input 2

```text
3 3
-1000000000 0 1000000000
1 3
2 3
1 1
```

### Sample Output 2

```text
-1000000000 1000000000 2000000000
0 1000000000 1000000000
-1000000000 -1000000000 0
```

### Giải thích

Ở ví dụ 1, độ cao thấp nhất và cao nhất của cả đoạn đường là $-2$ và $7$, nên độ chênh lệch bằng $9$. Hai điểm $3,4$ cùng có độ cao $7$. Đoạn $[2,5]$ vẫn có độ cao thấp nhất $-2$ và cao nhất $7$. Truy vấn cuối chỉ có một điểm nên độ chênh lệch bằng $0$.

Ở ví dụ 2, độ chênh lệch của cả đoạn là $10^9-(-10^9)=2\cdot10^9$.
