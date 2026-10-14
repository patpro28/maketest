# KNAPSACK29 — Ghép đường ray dài tới 10^18

### Đề bài

Có $N$ loại đoạn ray, loại $i$ dài $A_i$. Mỗi loại có số lượng không giới hạn. Bạn được nối các đoạn ray nhưng không được cắt chúng; tổng chiều dài là tổng chiều dài các đoạn đã lấy.

Có $Q$ truy vấn. Truy vấn $j$ yêu cầu xác định có thể ghép được **đúng** chiều dài $X_j$ hay không. Các truy vấn độc lập, không làm giảm số đoạn ray sẵn có. Khi $X_j=0$, được phép không lấy đoạn nào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, dòng thứ $j$ chứa số nguyên $X_j$.

### Dữ liệu ra

Với mỗi truy vấn, in `YES` hoặc `NO` trên một dòng theo thứ tự đầu vào.

### Ràng buộc

- $1\le N\le50$; $1\le Q\le100000$.
- $1\le A_i\le10^6$; $\min A_i\le5000$.
- $0\le X_j\le10^{18}$. Các chiều dài $A_i$ có thể trùng nhau.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $X_j\le10^5$ với mọi $j$ |
| 2 | 30% | $\min A_i\le100$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 6
4 7
0
5
8
11
13
1000000000000000000
```

### Sample Output 1

```text
YES
NO
YES
YES
NO
YES
```

### Sample Input 2

```text
2 4
6 10
12
14
16
999999999999999999
```

### Sample Output 2

```text
YES
NO
YES
NO
```

### Giải thích

Ở ví dụ 1, $8=4+4$, $11=4+7$, còn $5,13$ không ghép được. Chiều dài $10^{18}$ chia hết cho $4$. Ở ví dụ 2, $12=6+6$, $16=6+10$, còn $14$ không đạt được và chiều dài lẻ không thể ghép từ các đoạn chẵn.
