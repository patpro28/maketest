# SEGTREE200 — Tiền thưởng đồng loạt

### Đề bài

Có $N$ nhân viên được đánh số từ $1$ đến $N$. Nhân viên thứ $i$ có số dư tiền thưởng $A_i$; số dư có thể âm.

Thực hiện lần lượt $Q$ thao tác:

- `1 L R x`: cộng $x$ vào số dư của từng nhân viên có chỉ số thuộc $[L,R]$. Nếu $x$ âm, số dư của mỗi người trong đoạn bị trừ đi $|x|$.
- `2 p`: cho biết số dư hiện tại của nhân viên $p$.

Các lần cộng được tích lũy. Thao tác hỏi không làm thay đổi số dư.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: số dư hiện tại của nhân viên được hỏi. Thao tác loại `1` không yêu cầu in kết quả.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-1000000000\le A_i\le1000000000$ ở thời điểm ban đầu.
- Với thao tác loại `1`: $1\le L\le R\le N$.
- Với thao tác loại `1`: $-10^9\le x\le10^9$.
- Số dư sau các thao tác có thể nằm ngoài khoảng $[-10^9,10^9]$.
- Với thao tác loại `2`: $1\le p\le N$.

### Sample Input 1

```text
4 6
10 0 -5 7
2 3
1 1 3 4
2 1
1 2 4 -6
2 3
2 4
```

### Sample Output 1

```text
-5
14
-7
1
```

### Sample Input 2

```text
1 5
1000000000
1 1 1 1000000000
1 1 1 1000000000
2 1
1 1 1 -1000000000
2 1
```

### Sample Output 2

```text
3000000000
2000000000
```

### Giải thích

Ở ví dụ 1, số dư ban đầu của nhân viên $3$ là $-5$. Sau lần cộng đầu, dãy là $[14,4,-1,7]$, nên nhân viên $1$ có số dư $14$. Sau lần cộng thứ hai, dãy là $[14,-2,-7,1]$; hai câu trả lời cuối là $-7$ và $1$.

Ở ví dụ 2, hai lần cộng đầu làm số dư tăng lên $3000000000$. Sau khi trừ $1000000000$, số dư còn $2000000000$.
