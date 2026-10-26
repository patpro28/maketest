# SEGTREE002 — Các vị trí đạt chuẩn

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và một ngưỡng nguyên $K$. Vị trí $i$ được gọi là **đạt chuẩn** nếu $A_i\ge K$.

Bạn cần trả lời $Q$ truy vấn. Với mỗi đoạn $[l,r]$, hãy đếm số vị trí đạt chuẩn nằm trong đoạn đó.

Dãy số và ngưỡng $K$ đều được giữ nguyên trong suốt quá trình trả lời truy vấn. Hai vị trí có cùng giá trị vẫn được tính riêng.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $l,r$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa số vị trí đạt chuẩn trong đoạn được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i,K\le10^9$.
- Với mỗi truy vấn: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
6 4 5
5 2 8 5 -1 9
1 6
2 4
5 5
1 1
```

### Sample Output 1

```text
4
2
0
1
```

### Sample Input 2

```text
4 3 -2
-3 -2 0 -2
1 4
1 2
2 4
```

### Sample Output 2

```text
3
1
3
```

### Giải thích

Ở ví dụ 1, các vị trí $1,3,4,6$ đạt chuẩn. Đoạn $[2,4]$ có hai vị trí đạt chuẩn là $3$ và $4$. Vị trí $5$ không đạt chuẩn, còn vị trí $1$ có giá trị đúng bằng ngưỡng nên đạt chuẩn.

Ở ví dụ 2, ngưỡng là $-2$. Các giá trị $-2,0,-2$ đều đạt chuẩn, chỉ giá trị $-3$ không đạt chuẩn.
