# SEGTREE051 — Dấu của tích

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: xác định dấu của tích $A_l\cdot A_{l+1}\cdots A_r$.

Với mỗi truy vấn, chỉ cần biết tích âm, dương hay bằng $0$, không cần tính giá trị của tích. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa đúng một ký tự: `-` nếu tích âm, `+` nếu tích dương hoặc `0` nếu tích bằng $0$. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 7
-2 3 0 -4 5
2 1 2
2 1 5
1 3 -1
2 1 4
2 3 4
1 1 2
2 1 5
```

### Sample Output 1

```text
-
0
-
+
+
```

### Sample Input 2

```text
1 5
0
2 1 1
1 1 -1000000000
2 1 1
1 1 1000000000
2 1 1
```

### Sample Output 2

```text
0
-
+
```

### Giải thích

Ở ví dụ 1, tích trên đoạn $[1,2]$ là $-6$ nên mang dấu âm. Truy vấn toàn dãy đầu tiên có phần tử $0$ nên tích bằng $0$. Sau khi gán $A_3=-1$, đoạn $[1,4]$ có ba số âm nên tích âm, còn đoạn $[3,4]$ có hai số âm nên tích dương. Sau khi gán $A_1=2$, toàn dãy có hai số âm và không có số $0$ nên tích dương.

Ở ví dụ 2, dấu của tích chính là dấu của phần tử duy nhất tại thời điểm truy vấn.
