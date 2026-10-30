# PREFIX06 — Chia đội công bằng

### Đề bài

Có $N$ thành viên đứng thành hàng, thành viên thứ $i$ có năng lực $A_i$. Bạn chọn vị trí $i$ với $1\le i<N$ để chia hàng thành hai đội: đội trái gồm các vị trí từ $1$ đến $i$, đội phải gồm các vị trí từ $i+1$ đến $N$.

Một cách chia hợp lệ khi năng lực của **mọi** thành viên đội trái đều không lớn hơn năng lực của **mọi** thành viên đội phải. Hãy đếm số cách chia hợp lệ. Hai thành viên có năng lực bằng nhau được phép thuộc hai đội khác nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số cách chia hợp lệ.

### Ràng buộc

- $2\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
5
1 2 2 3 4
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
4
3 1 2 4
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, chia sau bất kỳ vị trí nào từ $1$ đến $4$ đều hợp lệ. Ở ví dụ 2, chỉ có thể chia sau vị trí $3$.
