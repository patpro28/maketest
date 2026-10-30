# PREFIX02 — Điểm cân bằng

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Vị trí $i$ là điểm cân bằng nếu tổng các phần tử đứng trước $i$ bằng tổng các phần tử đứng sau $i$. Không tính $A_i$ vào hai tổng. Tổng của một phần rỗng được quy ước bằng $0$.

Hãy tìm tất cả điểm cân bằng theo thứ tự chỉ số tăng dần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

Dòng đầu in số điểm cân bằng. Dòng thứ hai in các chỉ số cân bằng theo thứ tự tăng dần, cách nhau bởi dấu cách. Nếu không có điểm cân bằng, dòng thứ hai để trống.

### Ràng buộc

- $1\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
7
-7 1 5 2 -4 3 0
```

### Sample Output 1

```text
2
4 7
```

### Sample Input 2

```text
3
1 2 3
```

### Sample Output 2

```text
0

```

### Giải thích

Ở ví dụ 1, tại vị trí $4$, hai tổng đều bằng $-1$; tại vị trí $7$, hai tổng đều bằng $0$. Ở ví dụ 2, không vị trí nào có hai tổng bằng nhau.
