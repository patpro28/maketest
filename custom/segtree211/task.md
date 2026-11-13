# SEGTREE211 — Kho hàng vòng tròn

### Đề bài

Có $N$ kho xếp trên một vòng tròn theo thứ tự $1,2,\dots,N,1$. Kho $i$ có mức hàng $A_i$.

Đoạn từ $L$ đến $R$ đi theo chiều tăng chỉ số và tính cả hai đầu. Nếu $L>R$, đoạn gồm các kho $L,L+1,\dots,N,1,\dots,R$. Nếu $L=R$, đoạn chỉ gồm kho $L$.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào từng mức hàng trên đoạn vòng từ $L$ đến $R$.
- `2 L R`. In tổng mức hàng hiện tại trên đoạn vòng từ $L$ đến $R$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L,R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10^8$ ở đầu vào.

### Sample Input 1

```text
5 5
1 2 3 4 5
2 4 2
1 5 2 10
2 4 2
2 3 3
2 1 5
```

### Sample Output 1

```text
12
42
3
45
```

### Sample Input 2

```text
3 3
0 0 0
1 3 1 -2
2 3 2
2 1 1
```

### Sample Output 2

```text
-4
-2
```

### Giải thích

Ở ví dụ 1, đoạn $[4,2]$ trên vòng gồm các kho $4,5,1,2$. Cập nhật cộng $10$ cho ba kho $5,1,2$, nên tổng đoạn vòng tăng từ $12$ lên $42$. Kho $3$ giữ mức $3$ và tổng toàn vòng là $45$.

Ở ví dụ 2, cập nhật tác động lên kho $3$ và $1$. Hỏi từ $3$ đến $2$ đi qua cả ba kho và cho tổng $-4$.
