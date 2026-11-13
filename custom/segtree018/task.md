# SEGTREE018 — Tổng có hệ số cố định

### Đề bài

Có $N$ thiết bị. Thiết bị $i$ có số đo $A_i$ và hệ số hiệu chỉnh cố định $W_i$. Đóng góp của thiết bị vào báo cáo bằng $A_iW_i$.

Thực hiện lần lượt $Q$ thao tác.

- `1 i x`. Gán số đo $A_i=x$.
- `2 l r`. Tính tổng đóng góp hiện tại $\sum_{i=l}^{r} A_iW_i$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\dots,W_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in tổng được hỏi trên một dòng. Các kết quả xuất hiện theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $|A_i|\le10^9$ ở đầu vào.
- $|W_i|\le10000$ với mọi $1\le i\le N$.
- Với thao tác loại `1`, $1\le i\le N$ và $|x|\le10^9$.
- Với thao tác loại `2`, $1\le l\le r\le N$.

### Sample Input 1

```text
4 5
2 1 3 4
0 -2 5 -1
2 1 4
1 2 -3
2 2 4
1 1 100
2 1 2
```

### Sample Output 1

```text
9
17
6
```

### Sample Input 2

```text
3 4
1000000000 -1000000000 1000000000
10000 -10000 0
2 1 3
1 2 1000000000
2 1 3
2 3 3
```

### Sample Output 2

```text
20000000000000
0
0
```

### Giải thích

Ở ví dụ 1, ban đầu tổng là $0-2+15-4=9$. Sau khi sửa thiết bị $2$, đóng góp của ba thiết bị cuối là $6,15,-4$. Thiết bị $1$ có hệ số $0$, nên tổng của hai thiết bị đầu ở truy vấn cuối là $6$.

Ở ví dụ 2, hai thiết bị đầu ban đầu cùng đóng góp $10^{13}$. Sau khi đổi số đo của thiết bị $2$, hai đóng góp triệt tiêu nhau. Thiết bị $3$ luôn có đóng góp bằng $0$.
