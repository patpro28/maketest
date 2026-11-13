# SEGTREE017 — Tổng trên vành đai

### Đề bài

Có $N$ trạm nằm trên một vòng theo thứ tự $1,2,\dots,N,1$. Trạm $i$ ghi nhận giá trị $A_i$.

Đoạn từ $l$ đến $r$ đi theo chiều tăng chỉ số và tính cả hai đầu. Khi $l>r$, đoạn đi qua trạm $N$ rồi tiếp tục từ trạm $1$. Khi $l=r$, đoạn chỉ gồm một trạm.

Thực hiện lần lượt $Q$ thao tác.

- `1 i x`. Cộng $x$ vào giá trị của trạm $i$.
- `2 l r`. Tính tổng giá trị hiện tại trên đoạn vòng từ $l$ đến $r$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in tổng được hỏi trên một dòng. Các kết quả xuất hiện theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $|A_i|\le10^9$ ở đầu vào.
- Với thao tác loại `1`, $1\le i\le N$ và $|x|\le10^9$.
- Với thao tác loại `2`, $1\le l,r\le N$.

### Sample Input 1

```text
5 6
1 2 3 4 5
2 4 2
1 5 -8
2 4 2
2 5 5
1 1 10
2 5 1
```

### Sample Output 1

```text
12
4
-3
8
```

### Sample Input 2

```text
1 4
-3
2 1 1
1 1 1000000000
1 1 1000000000
2 1 1
```

### Sample Output 2

```text
-3
1999999997
```

### Giải thích

Ở ví dụ 1, đoạn vòng từ $4$ đến $2$ gồm các trạm $4,5,1,2$. Sau khi cộng $-8$ tại trạm $5$, tổng đoạn đó giảm từ $12$ xuống $4$. Ở truy vấn cuối, hai trạm $5$ và $1$ có giá trị $-3$ và $11$.

Ở ví dụ 2, vòng chỉ có một trạm. Giá trị của trạm tăng từ $-3$ lên $1999999997$ sau hai lần cộng.
