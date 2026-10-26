# SEGTREE101 — Số nhỏ nhất còn thiếu

### Đề bài

Một đa tập chỉ chứa các số nguyên từ $0$ đến $N$. Ban đầu, số $x$ xuất hiện $c_x$ lần. Thực hiện $Q$ thao tác:

- `1 x`: thêm một lần xuất hiện của $x$.
- `2 x`: xóa một lần xuất hiện của $x$. Bảo đảm $x$ đang có trong đa tập.

Sau **mỗi thao tác**, hãy tìm MEX của đa tập: số nguyên không âm nhỏ nhất chưa xuất hiện. Nếu mọi số từ $0$ đến $N$ đều có mặt, đáp án là $N+1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N+1$ số nguyên $c_0,c_1,\ldots,c_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Sau mỗi thao tác, in MEX trên một dòng.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le c_x\le10^9$ với $0\le x\le N$; giới hạn này áp dụng cho số lần xuất hiện ban đầu.
- $0\le x\le N$ trong mọi thao tác.
- Mỗi thao tác xóa đều hợp lệ.

### Sample Input 1

```text
3 5
1 0 2 0
1 1
2 0
1 3
1 0
2 2
```

### Sample Output 1

```text
3
0
0
4
4
```

### Sample Input 2

```text
1 4
0 0
1 1
1 0
2 1
2 0
```

### Sample Output 2

```text
0
2
1
0
```

### Giải thích

Ở ví dụ 1, sau thao tác đầu tiên chỉ còn số $3$ bị thiếu trong miền $[0,3]$. Sau khi xóa số $0$, MEX bằng $0$. Khi thêm lại số $0$ ở thao tác thứ tư, mọi giá trị trong miền đều xuất hiện nên MEX bằng $4$; xóa bớt một trong hai số $2$ không làm thay đổi đáp án. Ở ví dụ 2, MEX lần lượt là $0,2,1,0$.
