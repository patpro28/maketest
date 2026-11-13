# ICPC0711D — Biến đổi dãy số bằng phép XOR

### Đề bài

Cho hai dãy số $A,B$ đều có $N$ phần tử. Trong một bước, tính XOR của toàn bộ dãy $A$ hiện tại rồi thay một phần tử $A_i$ tùy chọn bằng giá trị đó. Hãy tìm số bước ít nhất để biến $A$ thành $B$, nghĩa là mọi phần tử ở cùng vị trí đều bằng nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\ldots,A_N$.
- Dòng thứ ba chứa $N$ số nguyên $B_1,\ldots,B_N$.

### Dữ liệu ra

In số bước ít nhất. Nếu không thể thực hiện, in `-1`.

### Ràng buộc

- $2\le N\le10^5$.
- $0\le A_i,B_i<2^{30}$.

### Sample Input 1

```text
3
0 1 2
3 1 0
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3
1 2 3
1 2 3
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
2
0 0
1 1
```

### Sample Output 3

```text
-1
```

### Sample Input 4

```text
4
3 2 1 0
1 2 0 3
```

### Sample Output 4

```text
3
```

### Giải thích

Ở ví dụ 1, thay $A_1$ bằng $3$ để được $(3,1,2)$, rồi thay $A_3$ bằng $0$ để được $(3,1,0)$.

Ở ví dụ 2, hai dãy đã bằng nhau. Ở ví dụ 3, mọi phép biến đổi đều giữ nguyên dãy toàn số $0$.

Ở ví dụ 4, lần lượt thay $A_3$ bằng $0$, $A_1$ bằng $1$, $A_4$ bằng $3$: $(3,2,1,0)\to(3,2,0,0)\to(1,2,0,0)\to(1,2,0,3)$.
