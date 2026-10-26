# PREFIX15 — Đoạn trên vòng tròn

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ xếp thành vòng tròn theo thứ tự chỉ số tăng dần; sau vị trí $N$ là vị trí $1$. Mỗi truy vấn gồm vị trí bắt đầu $L$ và độ dài $K$. Hãy tính tổng $K$ phần tử liên tiếp, bắt đầu từ vị trí $L$ và đi theo chiều tăng chỉ số. Vì $K\le N$, mỗi phần tử được tính nhiều nhất một lần trong một truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,K$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng các phần tử trên đoạn vòng tròn được hỏi.

### Ràng buộc

- $1\le N\le200000$.
- $1\le Q\le200000$.
- $-10^9\le A_i\le10^9$.
- $1\le L,K\le N$.

### Sample Input 1

```text
5 3
1 2 3 4 5
4 3
5 5
2 1
```

### Sample Output 1

```text
10
15
2
```

### Sample Input 2

```text
1 2
-7
1 1
1 1
```

### Sample Output 2

```text
-7
-7
```

### Giải thích

Ở ví dụ 1, truy vấn đầu đi qua các vị trí $4,5,1$, được tổng $4+5+1=10$. Truy vấn thứ hai đi đủ một vòng, được $15$. Truy vấn cuối chỉ lấy phần tử ở vị trí $2$, được $2$. Ở ví dụ 2, mọi truy vấn đều lấy phần tử duy nhất là $-7$.
