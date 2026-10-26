# SEGTREE172 — Thu thập đủ tín hiệu

### Đề bài

Mỗi vị trí $i$ chứa một mặt nạ bit $a_i$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l M`: tìm vị trí nhỏ nhất $r\in[l,N]$ sao cho $T=a_l\mathbin{\mathrm{OR}}\cdots\mathbin{\mathrm{OR}}a_r$ chứa đủ các bit của $M$, tức là $(T\mathbin{\mathrm{AND}}M)=M$. Nếu không có, in `-1`.

Mặt nạ $T$ được phép chứa thêm các bit không thuộc $M$. Các phép OR và AND đều là phép toán trên bit.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le a_i,x<2^{20}$; $1\le M<2^{20}$.
- $1\le i,l\le N$.

### Sample Input 1

```text
5 6
1 2 0 4 3
2 1 7
2 3 3
2 4 8
1 3 8
2 2 10
2 3 8
```

### Sample Output 1

```text
4
5
-1
3
3
```

### Sample Input 2

```text
2 4
0 0
2 1 1
1 2 1048575
2 1 3
2 2 1048575
```

### Sample Output 2

```text
-1
2
2
```

### Giải thích

Ở ví dụ 1, OR từ vị trí $1$ lần đầu chứa đủ các bit của $7$ tại vị trí $4$. Từ vị trí $3$, phải đến vị trí $5$ mới có đủ các bit của $3$. Bit của $8$ chưa xuất hiện trong đoạn $[4,5]$. Sau cập nhật, OR của đoạn $[2,3]$ là $10$. Ở ví dụ 2, các đáp án lần lượt là $-1,2,2$.
