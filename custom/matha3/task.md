# MATHA3 — Lịch bật đèn

### Đề bài

Một hệ thống đèn hoạt động theo chu kỳ: bật trong $A$ phút liên tiếp, sau đó tắt trong $B$ phút liên tiếp, rồi lặp lại như vậy mãi mãi. Các phút được đánh số từ $1$; phút thứ $1$ là phút đầu tiên đèn bật. Trạng thái của đèn không thay đổi trong mỗi phút.

Có $Q$ truy vấn độc lập. Mỗi truy vấn cho hai số nguyên $L,R$. Hãy đếm số phút đèn bật trong đoạn từ phút $L$ đến phút $R$, tính cả hai đầu mút.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $A,B,Q$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

In $Q$ dòng. Mỗi dòng chứa số phút đèn bật trong đoạn tương ứng, theo thứ tự truy vấn.

### Ràng buộc

- $1\le A,B\le10^6$.
- $1\le Q\le10^5$.
- $1\le L\le R\le10^{18}$ trong mỗi truy vấn.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 60% | $Q=1$, $L,R\le10^6$ |
| 2 | 30% | $A=1$ |
| 3 | 10% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 2 5
3 8
4 5
1 10
6 6
10 10
```

### Sample Output 1

```text
4
0
6
1
0
```

### Sample Input 2

```text
1 1 3
1 1000000000000000000
1000000000000000000 1000000000000000000
999999999999999999 1000000000000000000
```

### Sample Output 2

```text
500000000000000000
0
1
```

### Giải thích

Ở ví dụ 1, đèn bật trong các phút $1,2,3,6,7,8,11,12,13,\ldots$. Đoạn $[3,8]$ có bốn phút bật là $3,6,7,8$; đoạn $[4,5]$ không có phút bật nào. Trong mười phút đầu có sáu phút bật. Phút $6$ đèn bật, còn phút $10$ đèn tắt.

Ở ví dụ 2, đèn bật đúng vào các phút mang số lẻ. Vì vậy, trong $10^{18}$ phút đầu có $5\cdot10^{17}$ phút bật; phút $10^{18}$ đèn tắt, còn đoạn gồm hai phút cuối có một phút bật.
