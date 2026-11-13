# SEGTREE028 — Cực đại sau khi đổi dấu xen kẽ

### Đề bài

Cho dãy số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần xử lý lần lượt $Q$ thao tác.

- `1 i x` — gán giá trị $A_i$ bằng $x$.
- `2 l r` — trong đoạn $[l,r]$, xét các giá trị $A_l,-A_{l+1},A_{l+2},-A_{l+3},\ldots$ và tìm giá trị lớn nhất.

Dấu luôn bắt đầu bằng dấu cộng tại $l$. Phép đổi dấu chỉ dùng để tính đáp án của truy vấn hiện tại. Dãy $A$ chỉ thay đổi khi có thao tác gán.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa giá trị lớn nhất sau khi đổi dấu xen kẽ trong đoạn được hỏi. In các kết quả theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le 200\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- Với thao tác loại $1$, $1\le i\le N$ và $|x|\le 10^9$.
- Với thao tác loại $2$, $1\le l\le r\le N$.

### Sample Input 1

```text
5 6
4 -7 2 6 -3
2 1 5
2 2 5
1 4 -9
2 2 5
2 3 4
2 4 4
```

### Sample Output 1

```text
7
6
3
9
-9
```

### Sample Input 2

```text
2 4
-1000000000 1000000000
2 1 2
2 2 2
1 2 -1000000000
2 1 2
```

### Sample Output 2

```text
-1000000000
1000000000
1000000000
```

### Giải thích

Ở ví dụ 1, truy vấn đầu xét $4,7,2,-6,-3$, còn truy vấn thứ hai xét $-7,-2,6,3$. Sau khi gán $A_4=-9$, truy vấn trên $[2,5]$ xét $-7,-2,-9,3$. Truy vấn trên $[3,4]$ xét $2,9$, còn đoạn $[4,4]$ chỉ xét $-9$.

Ở ví dụ 2, cả hai giá trị sau khi đổi dấu trong truy vấn đầu đều bằng $-10^9$. Lần gán làm $A_2=-10^9$, nên truy vấn cuối xét $-10^9$ và $10^9$.
