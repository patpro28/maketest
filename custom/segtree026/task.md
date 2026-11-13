# SEGTREE026 — Cực đại ngoài vùng bảo trì

### Đề bài

Có $N$ trạm được đánh số từ $1$ đến $N$. Trạm $i$ có chỉ số hoạt động nguyên $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác.

- `1 i x` — gán chỉ số hoạt động của trạm $i$ bằng $x$.
- `2 l r u v` — trong các trạm từ $l$ đến $r$, bỏ qua các trạm từ $u$ đến $v$ và tìm chỉ số hoạt động lớn nhất của những trạm còn lại.

Vùng bảo trì $[u,v]$ nằm trong đoạn được hỏi $[l,r]$. Mỗi truy vấn luôn còn ít nhất một trạm để xét. Việc bỏ qua các trạm chỉ áp dụng cho truy vấn hiện tại.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo dạng `1 i x` hoặc `2 l r u v`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số hoạt động lớn nhất của các trạm được xét. In các kết quả theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le 200\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- Với thao tác loại $1$, $1\le i\le N$ và $|x|\le 10^9$.
- Với thao tác loại $2$, $1\le l\le u\le v\le r\le N$ và có ít nhất một trong hai bất đẳng thức $l<u$, $v<r$.

### Sample Input 1

```text
6 7
-8 9 -3 12 4 -6
2 1 6 2 4
2 2 5 2 3
1 4 -10
2 2 5 4 5
1 2 -11
2 1 4 2 3
2 3 6 3 5
```

### Sample Output 1

```text
4
12
9
-8
-6
```

### Sample Input 2

```text
2 4
-1 -1
2 1 2 1 1
1 2 1000000000
2 1 2 1 1
2 1 2 2 2
```

### Sample Output 2

```text
-1
1000000000
-1
```

### Giải thích

Ở ví dụ 1, truy vấn đầu xét các trạm $1,5,6$, có chỉ số lần lượt là $-8,4,-6$. Truy vấn thứ hai chỉ xét các trạm $4,5$. Sau hai lần gán, truy vấn trên $[1,4]$ bỏ qua $[2,3]$ và lấy giá trị lớn hơn giữa $-8$ và $-10$. Truy vấn cuối chỉ xét trạm $6$.

Ở ví dụ 2, mỗi truy vấn chỉ xét một trạm. Hai truy vấn đầu xét trạm $2$ trước và sau khi gán, còn truy vấn cuối xét trạm $1$.
