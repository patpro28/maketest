# PREFIX04 — Bình năng lượng

### Đề bài

Một robot đi qua $N$ trạm theo thứ tự từ $1$ đến $N$. Sau khi qua trạm $i$, năng lượng của robot thay đổi một lượng $A_i$: tăng nếu $A_i>0$, giảm nếu $A_i<0$. Năng lượng được phép bằng $0$.

Hãy tìm số nguyên không âm nhỏ nhất làm năng lượng ban đầu, sao cho năng lượng sau mỗi trạm đều không âm.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là năng lượng ban đầu nhỏ nhất cần có.

### Ràng buộc

- $1\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
5
-3 2 -4 6 -1
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
3
2 -1 -1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, năng lượng thay đổi tích lũy lần lượt là $-3,-1,-5,1,0$, nên cần ban đầu ít nhất $5$. Ở ví dụ 2, bắt đầu với $0$ vẫn đủ đi qua mọi trạm.
