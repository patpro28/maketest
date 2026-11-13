# SEGTREE214 — Tổng đan dấu sau cập nhật

### Đề bài

Cho dãy $A_1,\dots,A_N$. Tổng đan dấu của đoạn bắt đầu bằng dấu cộng tại phần tử đầu đoạn, sau đó dùng dấu trừ và dấu cộng xen kẽ.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào từng phần tử trong đoạn $[L,R]$.
- `2 L R`. In $A_L-A_{L+1}+A_{L+2}-\cdots$ đến hết đoạn $[L,R]$.

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
5 4
2 4 6 8 10
2 2 5
1 2 4 3
2 2 5
2 1 3
```

### Sample Output 1

```text
-4
-1
4
```

### Sample Input 2

```text
3 4
0 0 0
1 1 3 -5
2 1 2
2 2 2
2 1 3
```

### Sample Output 2

```text
0
-5
-5
```

### Giải thích

Ở ví dụ 1, ban đầu đoạn $[2,5]$ cho $4-6+8-10=-4$. Sau cập nhật, đoạn đó cho $7-9+11-10=-1$, còn đoạn $[1,3]$ cho $2-7+9=4$.

Ở ví dụ 2, mọi phần tử đều bằng $-5$. Hai số hạng của truy vấn đầu triệt tiêu. Truy vấn một hoặc ba phần tử đều cho $-5$.
