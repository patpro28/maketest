# SEGTREE000 — Nhật ký lượng mưa

### Đề bài

Một trạm khí tượng ghi lại lượng mưa trong $N$ ngày liên tiếp. Lượng mưa trong ngày thứ $i$ là $A_i$.

Bạn cần trả lời $Q$ truy vấn. Mỗi truy vấn gồm hai chỉ số $l,r$: hãy tính tổng lượng mưa từ ngày $l$ đến ngày $r$, bao gồm cả hai ngày này.

Dữ liệu lượng mưa được giữ nguyên trong suốt quá trình trả lời truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả lượng mưa trong từng ngày.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $l,r$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng lượng mưa trên đoạn ngày được hỏi.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 4
0 3 7 0 5
1 5
2 3
4 4
3 5
```

### Sample Output 1

```text
15
10
0
12
```

### Sample Input 2

```text
3 3
1000000000 1000000000 1000000000
1 3
2 2
2 3
```

### Sample Output 2

```text
3000000000
1000000000
2000000000
```

### Giải thích

Ở ví dụ 1, tổng lượng mưa trong cả $5$ ngày là $15$. Từ ngày $2$ đến ngày $3$ có tổng lượng mưa $3+7=10$. Ngày $4$ không có mưa. Ba ngày từ $3$ đến $5$ có tổng lượng mưa $7+0+5=12$.

Ở ví dụ 2, tổng lượng mưa trong cả $3$ ngày là $3\cdot10^9$, vượt phạm vi số nguyên có dấu 32 bit.
