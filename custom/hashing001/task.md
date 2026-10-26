# HASHING001 — Giai điệu chuyển tông

### Đề bài

Cho dãy cao độ $A_1,A_2,\ldots,A_n$ và đoạn nhạc mẫu $B_1,B_2,\ldots,B_m$.

Một vị trí bắt đầu $i$ hợp lệ nếu $1\le i\le n-m+1$ và tồn tại một số nguyên $c$ sao cho $A_{i+j-1}=B_j+c$ với mọi $1\le j\le m$. Giá trị $c$ có thể khác nhau giữa các vị trí bắt đầu.

Hãy đếm số vị trí bắt đầu hợp lệ. Các đoạn được phép chồng lấn. Nếu $m>n$, kết quả là $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,m$.
- Dòng thứ hai chứa $n$ số nguyên $A_1,A_2,\ldots,A_n$.
- Dòng thứ ba chứa $m$ số nguyên $B_1,B_2,\ldots,B_m$.

### Dữ liệu ra

In số vị trí bắt đầu hợp lệ.

### Ràng buộc

- $1\le n,m\le2\cdot10^5$.
- $-10^9\le A_i,B_j\le10^9$.

### Sample Input 1

```text
6 3
1 3 5 2 4 6
10 12 14
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
2 3
-1000000000 1000000000
0 1 2
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Đoạn bắt đầu tại $1$ là $(1,3,5)$, ứng với $c=-9$. Đoạn bắt đầu tại $4$ là $(2,4,6)$, ứng với $c=-8$. Không có vị trí nào khác hợp lệ.

**Ví dụ 2:** Đoạn mẫu dài hơn dãy $A$ nên không có vị trí hợp lệ.
