# SEGTREE122 — Khôi phục thứ tự xếp hàng

### Đề bài

Một hoán vị $a_1,\ldots,a_N$ chứa mỗi số từ $1$ đến $N$ đúng một lần. Với mỗi vị trí $i$, biết $e_i$ là số vị trí $j<i$ thỏa mãn $a_j>a_i$.

Cho dãy $e_1,\ldots,e_N$ với $0\le e_i<i$. Hãy khôi phục hoán vị ban đầu. Với các điều kiện này, hoán vị tồn tại và là duy nhất.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $e_1,\ldots,e_N$.

### Dữ liệu ra

In $N$ số nguyên $a_1,\ldots,a_N$ trên một dòng, cách nhau bởi dấu cách.

### Ràng buộc

- $1\le N\le200000$.
- $0\le e_i<i$ với $1\le i\le N$.

### Sample Input 1

```text
5
0 1 0 2 1
```

### Sample Output 1

```text
3 1 5 2 4
```

### Sample Input 2

```text
4
0 1 2 3
```

### Sample Output 2

```text
4 3 2 1
```

### Giải thích

Ở ví dụ 1, hoán vị là $(3,1,5,2,4)$. Trước số $2$ ở vị trí $4$ có hai số lớn hơn là $3$ và $5$; trước số $4$ ở vị trí cuối có một số lớn hơn là $5$. Ở ví dụ 2, mỗi phần tử nhỏ hơn mọi phần tử đứng trước nó nên hoán vị giảm dần.
