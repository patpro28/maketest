# SEGTREE016 — Chuyển hàng giữa hai kho

### Đề bài

Có $N$ kho được đánh số từ $1$ đến $N$. Số dư hàng của kho $i$ là $A_i$. Số dư âm biểu thị lượng hàng kho đang nợ.

Thực hiện lần lượt $Q$ thao tác.

- `1 u v x`. Chuyển $x$ đơn vị từ kho $u$ sang kho $v$. Giảm số dư kho $u$ đi $x$ và tăng số dư kho $v$ thêm $x$. Bạn vẫn thực hiện thao tác khi số dư kho $u$ nhỏ hơn $x$. Nếu $u=v$, hai thay đổi triệt tiêu nhau.
- `2 l r`. Tính tổng số dư hiện tại của các kho từ $l$ đến $r$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng `1 u v x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in tổng được hỏi trên một dòng. Các kết quả xuất hiện theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $|A_i|\le10^9$ ở đầu vào.
- Với thao tác loại `1`, $1\le u,v\le N$ và $0\le x\le10^9$.
- Với thao tác loại `2`, $1\le l\le r\le N$.

### Sample Input 1

```text
5 7
5 -2 4 1 0
2 1 5
1 1 4 3
2 1 3
1 4 4 9
2 4 5
1 2 5 2
2 2 5
```

### Sample Output 1

```text
8
4
4
6
```

### Sample Input 2

```text
2 6
0 0
1 1 2 1000000000
1 1 2 1000000000
1 1 2 1000000000
2 1 1
2 2 2
2 1 2
```

### Sample Output 2

```text
-3000000000
3000000000
0
```

### Giải thích

Ở ví dụ 1, ban đầu tổng số dư là $8$. Sau khi chuyển $3$ đơn vị từ kho $1$ sang kho $4$, dãy là $[2,-2,4,4,0]$. Chuyển hàng từ kho $4$ sang chính kho đó giữ số dư bằng $4$. Lần chuyển cuối đưa dãy thành $[2,-4,4,4,2]$, nên tổng đoạn $[2,5]$ là $6$.

Ở ví dụ 2, sau ba lần chuyển, kho $1$ nợ $3\cdot10^9$ đơn vị và kho $2$ có $3\cdot10^9$ đơn vị. Tổng số dư của hai kho là $0$.
