# SEGTREE019 — Tổng theo bước nhảy

### Đề bài

Cho dãy $A_1,A_2,\dots,A_N$ và bước nhảy cố định $K$. Một tuyến bắt đầu tại $l$ và kết thúc trước hoặc tại $r$ gồm các vị trí $l,l+K,l+2K,\dots$ không vượt quá $r$. Tuyến luôn chứa vị trí $l$.

Thực hiện lần lượt $Q$ thao tác.

- `1 i x`. Gán $A_i=x$.
- `2 l r`. Tính tổng giá trị hiện tại ở các vị trí trên tuyến bắt đầu tại $l$ và không vượt quá $r$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in tổng được hỏi trên một dòng. Các kết quả xuất hiện theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,Q\le200000$.
- $|A_i|\le10^9$ ở đầu vào.
- $1\le K\le N$.
- Với thao tác loại `1`, $1\le i\le N$ và $|x|\le10^9$.
- Với thao tác loại `2`, $1\le l\le r\le N$.

### Sample Input 1

```text
8 5 3
1 2 3 4 5 6 7 8
2 2 8
1 4 -4
2 1 8
2 2 7
2 4 6
```

### Sample Output 1

```text
15
4
7
-4
```

### Sample Input 2

```text
4 4 4
4 3 2 1
1 4 -5
2 4 4
2 1 4
2 2 4
```

### Sample Output 2

```text
-5
4
3
```

### Giải thích

Ở ví dụ 1, tuyến đầu gồm các vị trí $2,5,8$, có tổng $15$. Sau khi gán $A_4=-4$, tuyến $1,4,7$ cho tổng $4$. Hai tuyến cuối lần lượt gồm $2,5$ và chỉ vị trí $4$.

Ở ví dụ 2, vì $K=N$, mỗi tuyến chỉ chứa vị trí đầu. Cập nhật tại vị trí $4$ cho kết quả $-5$ khi hỏi tuyến bắt đầu ở đó.
