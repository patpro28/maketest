# KNAPSACK15 — Xây số lớn nhất

### Đề bài

Bạn có đúng $N$ đồng. Viết một chữ số $d$ tốn $C_d$ đồng, với $d=0,1,\ldots,9$. Mỗi chữ số có thể được viết nhiều lần.

Hãy tạo một số nguyên không âm lớn nhất bằng cách dùng **đúng** $N$ đồng. Biểu diễn phải có ít nhất một chữ số và không có chữ số $0$ ở đầu, ngoại trừ số $0$ được viết bằng đúng một chữ số.

Nếu không thể viết một số hợp lệ với đúng số tiền đang có, hãy báo không thể.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa mười số nguyên $C_0,C_1,\ldots,C_9$ theo thứ tự chữ số.

### Dữ liệu ra

In số nguyên lớn nhất dưới dạng một chuỗi chữ số; in `-1` nếu không tồn tại số hợp lệ.

### Ràng buộc

- $1\le N\le10000$.
- $1\le C_d\le10000$ với mọi $0\le d\le9$.
- Đáp án có thể rất dài; không yêu cầu lưu đáp án trong kiểu số nguyên. Các chữ số được dùng không giới hạn số lần.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $C_0=C_1=\cdots=C_9$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
1 2 3 4 5 6 7 8 9 10
```

### Sample Output 1

```text
1000
```

### Sample Input 2

```text
3
2 2 2 2 2 2 2 2 2 2
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, viết $1000$ tốn $2+1+1+1=5$ đồng. Không thể viết số hợp lệ có năm chữ số vì chữ số khác $0$ rẻ nhất tốn $2$ đồng. Ở ví dụ 2, mọi số đều có chi phí chẵn.
