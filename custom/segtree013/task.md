# SEGTREE013 — Tổng đan dấu

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: tính tổng đan dấu $A_l-A_{l+1}+A_{l+2}-A_{l+3}+\cdots+(-1)^{r-l}A_r$.

Trong mỗi truy vấn, phần tử đầu đoạn luôn có dấu cộng, sau đó dấu trừ và dấu cộng xen kẽ nhau, bất kể $l$ chẵn hay lẻ. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa tổng đan dấu của đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
5 7
3 1 4 1 5
2 1 5
2 2 5
2 3 3
1 2 -2
2 1 3
1 4 6
2 2 5
```

### Sample Output 1

```text
10
-7
4
9
-5
```

### Sample Input 2

```text
4 4
1000000000 -1000000000 1000000000 -1000000000
2 1 4
2 2 4
1 3 -1000000000
2 1 4
```

### Sample Output 2

```text
4000000000
-3000000000
2000000000
```

### Giải thích

Ở ví dụ 1, truy vấn đầu tính $3-1+4-1+5=10$. Truy vấn thứ hai bắt đầu ở vị trí $2$ nhưng vẫn bắt đầu bằng dấu cộng: $1-4+1-5=-7$. Đoạn một phần tử trả về chính giá trị của phần tử đó. Sau hai lần gán, hai kết quả tiếp theo lần lượt là $3-(-2)+4=9$ và $-2-4+6-5=-5$.

Ở ví dụ 2, các giá trị và các dấu của truy vấn đầu làm cả bốn số hạng đều bằng $10^9$, nên tổng là $4\cdot10^9$.
