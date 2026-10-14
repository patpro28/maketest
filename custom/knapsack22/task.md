# KNAPSACK22 — Pha đồ uống đúng độ ngọt

### Đề bài

Có $N$ công thức đồ uống. Mỗi lần dùng công thức $i$ tạo một cốc có độ ngọt $A_i$. Tất cả các cốc có cùng thể tích; mỗi công thức được dùng không giới hạn số lần.

Hãy đếm số cách làm **đúng $K$ cốc** sao cho độ ngọt trung bình bằng $T$. Một cách được xác định bởi số cốc làm theo từng công thức, không phân biệt thứ tự.

Các công thức có mã khác nhau được xem là khác nhau, kể cả khi cùng độ ngọt. Lấy kết quả theo modulo $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,K,T$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\ldots,A_N$.

### Dữ liệu ra

In số cách làm đồ uống thỏa mãn modulo $10^9+7$.

### Ràng buộc

- $1\le N,K\le40$.
- $1\le T,A_i\le50$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N,K\le5$ |
| 2 | 30% | $K\le10$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 3 2
1 2 3
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
2 3 2
1 3
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, dùng công thức thứ hai ba lần, hoặc dùng mỗi công thức một lần. Ở ví dụ 2, tổng độ ngọt của ba cốc luôn lẻ, không thể bằng $KT=6$.
