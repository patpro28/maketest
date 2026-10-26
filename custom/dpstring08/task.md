# DPSTRING08 — Tránh mẫu aba

### Đề bài

Cho xâu $S$ chỉ gồm `a` và `b`, gồm $N$ ký tự. Chi phí xóa ký tự ở vị trí $i$ là $W_i$.

Hãy tìm tổng chi phí xóa nhỏ nhất để xâu còn lại không chứa đoạn con liên tiếp `aba`. Các ký tự còn lại giữ nguyên thứ tự ban đầu. Mẫu cấm được xét trong xâu sau khi xóa, vì vậy những ký tự không kề nhau ban đầu có thể trở thành kề nhau.

Được phép xóa hết xâu hoặc không xóa ký tự nào.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- Mỗi ký tự của $S$ thuộc tập `a`, `b`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
3
aba
5 1 4
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
4
abba
8 1 2 9
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, xóa chữ `b` ở giữa với chi phí $1$, còn `aa`. Ở ví dụ 2, xâu `abba` không chứa đoạn liên tiếp `aba`, nên không cần xóa. Việc xóa chỉ một trong hai chữ `b` lại tạo ra mẫu cấm.
