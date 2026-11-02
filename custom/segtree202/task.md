# SEGTREE202 — Mức hỗ trợ tối thiểu

### Đề bài

Có $N$ người được đánh số từ $1$ đến $N$. Mức hỗ trợ hiện tại của người thứ $i$ là $A_i$.

Thực hiện lần lượt $Q$ thao tác:

- `1 L R x`: bảo đảm mỗi người trong đoạn $[L,R]$ nhận mức hỗ trợ ít nhất là $x$. Với mỗi $i\in[L,R]$, thay $A_i$ bằng $\max(A_i,x)$.
- `2 p`: cho biết mức hỗ trợ hiện tại của người $p$.

Một mức hỗ trợ đã cao hơn hoặc bằng $x$ được giữ nguyên; thao tác loại `1` không bao giờ làm giảm mức hỗ trợ.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: mức hỗ trợ hiện tại của người được hỏi. Thao tác loại `1` không yêu cầu in kết quả.

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
2 3
2 4
```

### Sample Output 1

```text
8
6
6
5
```

### Sample Input 2

```text
1 5
0
1 1 1 5
1 1 1 3
2 1
1 1 1 10
2 1
```

### Sample Output 2

```text
5
10
```

### Giải thích

Ở ví dụ 1, thao tác đầu tạo dãy $[6,8,6,5]$. Người $2$ vẫn có mức hỗ trợ $8$, còn người $3$ có mức hỗ trợ $6$. Áp dụng mức tối thiểu $4$ cho đoạn $[2,4]$ không làm thay đổi phần tử nào, nên hai câu trả lời cuối là $6$ và $5$.

Ở ví dụ 2, nâng mức hỗ trợ lên ít nhất $5$ rồi áp dụng mức tối thiểu $3$ vẫn giữ giá trị $5$. Thao tác cuối cùng nâng mức hỗ trợ lên $10$.
