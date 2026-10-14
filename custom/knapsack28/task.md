# KNAPSACK28 — Xây số lớn nhất chia hết

### Đề bài

Viết một chữ số $d$ tốn $C_d$ đồng, với $d=0,1,\ldots,9$. Mỗi chữ số được dùng không giới hạn số lần.

Với **đúng** $B$ đồng, hãy viết số nguyên không âm lớn nhất chia hết cho $M$. Biểu diễn phải có ít nhất một chữ số và không có chữ số $0$ ở đầu, ngoại trừ số $0$ được viết bằng đúng một chữ số. Số $0$ chia hết cho mọi $M>0$.

Nếu không thể viết một số hợp lệ, hãy báo không thể. Đáp án có thể rất dài, cần in dưới dạng chuỗi chữ số.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $B,M$.
- Dòng thứ hai chứa mười số nguyên $C_0,C_1,\ldots,C_9$.

### Dữ liệu ra

In số nguyên lớn nhất thỏa mãn; in `-1` nếu không có phương án.

### Ràng buộc

- $1\le B\le2000$; $1\le M\le50$.
- $1\le C_d\le2000$ với mọi $0\le d\le9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $B\le10$ |
| 2 | 30% | $M=1$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4 2
1 2 2 2 2 2 2 2 2 2
```

### Sample Output 1

```text
900
```

### Sample Input 2

```text
3 2
2 2 2 2 2 2 2 2 2 2
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, số $900$ tốn $2+1+1=4$ đồng, chia hết cho $2$, và có độ dài lớn nhất có thể. Ở ví dụ 2, mọi chi phí đều chẵn nên không dùng đúng $3$ đồng được.
