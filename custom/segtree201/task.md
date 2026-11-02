# SEGTREE201 — Sơn lại các ô

### Đề bài

Có $N$ ô nằm trên một hàng, đánh số từ $1$ đến $N$. Ô thứ $i$ có mã màu $A_i$, là một số nguyên không âm. Mã màu $0$ cũng là một màu hợp lệ.

Thực hiện lần lượt $Q$ thao tác:

- `1 L R c`: sơn toàn bộ các ô trong đoạn $[L,R]$ thành màu $c$, thay thế màu cũ của các ô đó.
- `2 p`: cho biết mã màu hiện tại của ô $p$.

Nếu một ô được sơn nhiều lần, màu của nó là màu ở lần sơn gần nhất tác động tới ô đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: mã màu hiện tại của ô được hỏi. Thao tác loại `1` không yêu cầu in kết quả.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le1000000000$ ở thời điểm ban đầu.
- Với thao tác loại `1`: $1\le L\le R\le N$.
- Với thao tác loại `1`: $0\le c\le10^9$.
- Với thao tác loại `2`: $1\le p\le N$.

### Sample Input 1

```text
5 7
1 2 3 4 5
1 1 5 0
2 3
1 2 4 7
2 1
2 3
1 3 3 0
2 3
```

### Sample Output 1

```text
0
0
7
0
```

### Sample Input 2

```text
3 5
8 8 8
2 2
1 1 2 3
1 2 3 9
2 1
2 2
```

### Sample Output 2

```text
8
3
9
```

### Giải thích

Ở ví dụ 1, sau lần sơn đầu tiên, cả năm ô đều có màu $0$. Sơn đoạn $[2,4]$ thành màu $7$ tạo dãy màu $[0,7,7,7,0]$. Sơn tiếp riêng ô $3$ thành màu $0$ tạo dãy $[0,7,0,7,0]$. Các câu trả lời lần lượt là $0,0,7,0$.

Ở ví dụ 2, hai lần sơn tạo dãy màu cuối cùng $[3,9,9]$. Màu ban đầu của ô $2$ là $8$; hai câu trả lời sau cùng là $3$ và $9$.
