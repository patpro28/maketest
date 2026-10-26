# SEGTREE070 — Tổng có trọng số

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: tính tổng có trọng số $A_l+2A_{l+1}+3A_{l+2}+\cdots+(r-l+1)A_r$.

Trọng số luôn bắt đầu từ $1$ ở đầu mỗi đoạn truy vấn, không phụ thuộc chỉ số $l$ trong dãy. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa tổng có trọng số của đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^8\le A_i,x\le10^8$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
5 6
2 -1 3 0 4
2 1 5
2 2 4
1 3 -2
2 2 5
1 2 5
2 1 3
```

### Sample Output 1

```text
29
5
11
6
```

### Sample Input 2

```text
7 4
100000000 100000000 100000000 100000000 100000000 100000000 100000000
2 1 7
2 3 7
1 4 -100000000
2 1 7
```

### Sample Output 2

```text
2800000000
1500000000
2000000000
```

### Giải thích

Ở ví dụ 1, truy vấn đầu tính $2+2\cdot(-1)+3\cdot3+4\cdot0+5\cdot4=29$. Đoạn $[2,4]$ tính $-1+2\cdot3+3\cdot0=5$. Sau lần gán thứ nhất, đoạn $[2,5]$ có tổng $-1+2\cdot(-2)+3\cdot0+4\cdot4=11$. Sau lần gán thứ hai, đoạn $[1,3]$ cho kết quả $2+2\cdot5+3\cdot(-2)=6$.

Ở ví dụ 2, tổng đầu tiên là $(1+2+\cdots+7)\cdot10^8=2{,}8\cdot10^9$. Sửa phần tử thứ $4$ từ $10^8$ thành $-10^8$ làm tổng trên cả dãy giảm $8\cdot10^8$.
