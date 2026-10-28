# MANGDONG — Mạng liên lạc biến động

### Đề bài

Có $N$ khu dân cư được đánh số từ $1$ đến $N$. Mỗi khu có một màu cố định: $0$ là đỏ, $1$ là xanh. Ban đầu chưa có đường nối giữa các khu.

Bạn cần xử lý $Q$ thao tác theo đúng thứ tự:

- `+ u v`: thêm một đường hai chiều nối hai khu khác nhau $u,v$. Trước thao tác này, đường giữa chúng chưa tồn tại.
- `- u v`: xóa đường hai chiều đang tồn tại giữa $u,v$.
- `?`: hỏi số cặp gồm một khu đỏ và một khu xanh đang liên thông. Hai khu liên thông nếu có thể đi từ khu này đến khu kia qua các đường đang tồn tại.

Mỗi cặp đỏ–xanh chỉ được tính một lần, không phụ thuộc số đường đi nối chúng. Đường đã xóa có thể được thêm lại ở thao tác sau. Hai cách viết `u v` và `v u` chỉ cùng một đường.

Hãy trả lời mọi thao tác `?`.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $C_1,C_2,\ldots,C_N$, trong đó $C_i$ là màu của khu $i$.
- Trong $Q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo một trong ba dạng `+ u v`, `- u v`, `?`.

### Dữ liệu ra

Với mỗi thao tác `?`, in số cặp đỏ–xanh đang liên thông trên một dòng, theo thứ tự xuất hiện của các thao tác hỏi.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $C_i\in\{0,1\}$.
- Với thao tác thêm hoặc xóa: $1\le u,v\le N$, $u\ne v$.
- Các thao tác thêm và xóa luôn thỏa điều kiện tồn tại đường như mô tả.
- Có ít nhất một thao tác `?`.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 30% | $N,Q\le2000$ |
| 2 | 30% | Không có thao tác xóa đường |
| 3 | 40% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4 10
0 1 0 1
?
+ 1 2
?
+ 2 3
?
+ 3 4
?
- 2 3
?
?
```

### Sample Output 1

```text
0
1
2
4
2
2
```

### Sample Input 2

```text
3 5
0 0 0
+ 1 2
+ 2 3
?
- 1 2
?
```

### Sample Output 2

```text
0
0
```

### Sample Input 3

```text
2 7
0 1
+ 1 2
?
- 2 1
?
+ 2 1
?
?
```

### Sample Output 3

```text
1
0
1
1
```

### Giải thích

Ở ví dụ 1, sau khi thêm cả ba đường, bốn khu cùng liên thông, có $2\cdot2=4$ cặp đỏ–xanh. Khi xóa đường giữa $2$ và $3$, mạng tách thành hai thành phần $\{1,2\}$ và $\{3,4\}$; mỗi thành phần đóng góp một cặp.

Ở ví dụ 2, không có khu xanh nên mọi câu trả lời đều bằng $0$.

Ở ví dụ 3, đường nối hai khu được thêm, xóa rồi thêm lại. Thứ tự ghi hai đầu đường không làm thay đổi đường được nói tới.
