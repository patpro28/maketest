# SEGTREE210 — Sổ thu chi

### Đề bài

Cho dãy số dư $A_1,\dots,A_N$.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào từng số dư trong đoạn $[L,R]$.
- `2 L R`. In tổng số dư hiện tại của đoạn $[L,R]$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10^8$ ở đầu vào.

### Sample Input 1

```text
5 5
1 -2 3 0 4
2 1 5
1 2 4 3
2 2 4
1 1 5 -2
2 1 3
```

### Sample Output 1

```text
6
10
2
```

### Sample Input 2

```text
1 4
-5
1 1 1 0
2 1 1
1 1 1 7
2 1 1
```

### Sample Output 2

```text
-5
2
```

### Giải thích

Ở ví dụ 1, ban đầu tổng là $6$. Sau lần cộng đầu, đoạn $[2,4]$ là $[1,6,3]$, tổng $10$. Sau lần cộng cuối, ba phần tử đầu là $[-1,-1,4]$, tổng $2$.

Ở ví dụ 2, cộng $0$ giữ giá trị $-5$. Sau khi cộng $7$, giá trị là $2$.
