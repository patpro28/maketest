# SEGTREE050 — Thống kê chẵn lẻ

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: đếm số phần tử chẵn và số phần tử lẻ trong đoạn từ vị trí $l$ đến vị trí $r$.

Số $0$ là số chẵn. Các số âm cũng được phân loại chẵn lẻ theo tính chia hết cho $2$. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm hai số nguyên: số phần tử chẵn rồi đến số phần tử lẻ trong đoạn được hỏi. Hai số cách nhau một dấu cách. Nếu không có thao tác loại $2$, không in gì.

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
6 6
-3 0 4 7 -2 5
2 1 6
2 2 5
1 4 8
2 3 6
1 2 -5
2 1 2
```

### Sample Output 1

```text
3 3
3 1
3 1
0 2
```

### Sample Input 2

```text
1 5
0
2 1 1
1 1 -7
2 1 1
1 1 -8
2 1 1
```

### Sample Output 2

```text
1 0
0 1
1 0
```

### Giải thích

Ở ví dụ 1, ba số chẵn ban đầu là $0,4,-2$. Đoạn $[2,5]$ gồm $0,4,7,-2$ nên có $3$ số chẵn và $1$ số lẻ. Sau khi gán $A_4=8$, đoạn $[3,6]$ gồm $4,8,-2,5$. Sau khi gán $A_2=-5$, cả hai phần tử trong đoạn $[1,2]$ đều lẻ.

Ở ví dụ 2, phần tử duy nhất lần lượt là $0$, $-7$, $-8$, tương ứng chẵn, lẻ, chẵn.
