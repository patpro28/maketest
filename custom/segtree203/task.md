# SEGTREE203 — Giới hạn hạn mức

### Đề bài

Có $N$ tài khoản được đánh số từ $1$ đến $N$. Tài khoản thứ $i$ có hạn mức hiện tại $A_i$.

Thực hiện lần lượt $Q$ thao tác:

- `1 L R x`: giới hạn hạn mức của mỗi tài khoản trong đoạn $[L,R]$ ở mức không quá $x$. Với mỗi $i\in[L,R]$, thay $A_i$ bằng $\min(A_i,x)$.
- `2 p`: cho biết hạn mức hiện tại của tài khoản $p$.

Một hạn mức đã nhỏ hơn hoặc bằng $x$ được giữ nguyên; thao tác loại `1` không bao giờ làm tăng hạn mức.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: hạn mức hiện tại của tài khoản được hỏi. Thao tác loại `1` không yêu cầu in kết quả.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le1000000000$ ở thời điểm ban đầu.
- Với thao tác loại `1`: $1\le L\le R\le N$.
- Với thao tác loại `1`: $0\le x\le10^9$.
- Với thao tác loại `2`: $1\le p\le N$.

### Sample Input 1

```text
4 6
2 8 1 5
1 1 3 6
2 2
2 3
1 2 4 4
2 2
2 4
```

### Sample Output 1

```text
6
1
4
4
```

### Sample Input 2

```text
1 5
10
1 1 1 5
1 1 1 7
2 1
1 1 1 0
2 1
```

### Sample Output 2

```text
5
0
```

### Giải thích

Ở ví dụ 1, thao tác đầu tạo dãy $[2,6,1,5]$, nên hai câu trả lời đầu là $6$ và $1$. Giới hạn đoạn $[2,4]$ ở mức $4$ tạo dãy $[2,4,1,4]$, nên hai câu trả lời cuối đều là $4$.

Ở ví dụ 2, hạn mức giảm từ $10$ xuống $5$. Áp dụng trần $7$ không làm tăng hạn mức, nên câu trả lời đầu là $5$. Sau khi áp dụng trần $0$, câu trả lời là $0$.
