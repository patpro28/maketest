# SEGTREE021 — Vị trí thấp nhất

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: tìm giá trị nhỏ nhất trong đoạn $[l,r]$ và vị trí xuất hiện đầu tiên của giá trị đó trong đoạn.

Nếu có nhiều vị trí cùng mang giá trị nhỏ nhất, chọn vị trí có chỉ số nhỏ nhất. Chỉ số trả về là chỉ số trong dãy ban đầu, được đánh số từ $1$, không phải thứ tự tương đối trong đoạn truy vấn. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm hai số nguyên: giá trị nhỏ nhất và chỉ số xuất hiện đầu tiên của giá trị đó trong đoạn được hỏi. Hai số cách nhau một dấu cách. Nếu không có thao tác loại $2$, không in gì.

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
6 7
4 -2 3 -2 -2 5
2 1 6
2 3 5
1 2 7
2 1 6
1 4 0
2 3 6
2 6 6
```

### Sample Output 1

```text
-2 2
-2 4
-2 4
-2 5
5 6
```

### Sample Input 2

```text
3 5
8 8 8
2 2 3
1 1 -1
2 1 3
1 2 -1
2 2 3
```

### Sample Output 2

```text
8 2
-1 1
-1 2
```

### Giải thích

Ở ví dụ 1, giá trị nhỏ nhất ban đầu là $-2$ xuất hiện ở các vị trí $2,4,5$, nên truy vấn toàn dãy đầu tiên chọn vị trí $2$. Truy vấn $[3,5]$ chọn vị trí $4$. Sau hai lần cập nhật, vị trí xuất hiện đầu tiên của giá trị nhỏ nhất trong các đoạn được hỏi thay đổi như kết quả. Truy vấn một phần tử cuối cùng trả về giá trị $5$ và chỉ số $6$.

Ở ví dụ 2, truy vấn đầu chọn chỉ số $2$ dù các giá trị bằng nhau. Hai truy vấn còn lại chọn vị trí có giá trị $-1$ nằm trong đoạn được hỏi.
