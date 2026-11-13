# SEGTREE218 — Tổng tải trên trục dài

### Đề bài

Trên một tuyến đường có $10^9$ vị trí nguyên từ $1$ đến $10^9$. Ban đầu tải tại mỗi vị trí bằng $0$.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào tải tại từng vị trí nguyên từ $L$ đến $R$, kể cả hai đầu.
- `2 L R`. In tổng tải hiện tại tại tất cả vị trí nguyên từ $L$ đến $R$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $Q$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le Q\le200000$.
- $1\le L\le R\le10^9$ với mỗi thao tác.
- $|X|\le10000$ đối với thao tác loại `1`.

### Sample Input 1

```text
6
1 2 5 3
2 1 5
1 4 7 -1
2 3 6
2 7 7
2 8 1000000000
```

### Sample Output 1

```text
12
6
-1
0
```

### Sample Input 2

```text
4
1 1 1000000000 10000
2 1 1000000000
1 1000000000 1000000000 -10000
2 999999999 1000000000
```

### Sample Output 2

```text
10000000000000
10000
```

### Giải thích

Ở ví dụ 1, lần cộng đầu tạo tổng $4\cdot3=12$. Sau cập nhật thứ hai, tải ở các vị trí $3,4,5,6$ lần lượt là $3,2,2,-1$, có tổng $6$. Vị trí $7$ có tải $-1$, còn từ $8$ trở đi tải bằng $0$.

Ở ví dụ 2, lần cộng toàn trục cho tổng $10^{13}$. Cập nhật kế tiếp đưa tải tại vị trí cuối về $0$, nên hai vị trí cuối có tổng $10000$.
