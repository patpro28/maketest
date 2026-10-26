# SEGTREE131 — Điểm cân bằng dân cư

### Đề bài

Có $N$ địa điểm theo thứ tự trên một tuyến đường. Địa điểm $i$ có $w_i$ người. Thực hiện các thao tác:

- `1 i x`: gán dân số địa điểm $i$ bằng $x$.
- `2 l r`: đặt $W=w_l+\cdots+w_r$. Tìm vị trí nhỏ nhất $p\in[l,r]$ sao cho $2(w_l+\cdots+w_p)\ge W$. Nếu $W=0$, quy ước đáp án là $l$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $w_1,\ldots,w_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le w_i,x\le10^9$.
- $1\le i\le N$; $1\le l\le r\le N$.

### Sample Input 1

```text
5 5
0 2 0 2 0
2 1 5
2 3 5
1 2 0
2 1 3
2 2 5
```

### Sample Output 1

```text
2
4
1
4
```

### Sample Input 2

```text
3 5
1000000000 1000000000 1000000000
2 1 3
2 2 3
1 2 0
2 1 3
2 2 2
```

### Sample Output 2

```text
2
2
1
2
```

### Giải thích

Ở ví dụ 1, hai truy vấn đầu có đáp án $2$ và $4$. Sau khi dân số địa điểm $2$ về $0$, đoạn $[1,3]$ có tổng bằng $0$ nên trả về $1$; đoạn $[2,5]$ đạt ngưỡng tại địa điểm $4$. Ở ví dụ 2, các đáp án lần lượt là $2,2,1,2$; cần lưu tổng dân số bằng số nguyên 64 bit.
