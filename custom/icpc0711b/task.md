# ICPC0711B — Phần tử trung vị

### Đề bài

Trung vị của một dãy có $m$ phần tử là phần tử ở vị trí $\lfloor m/2\rfloor+1$ sau khi sắp xếp dãy không giảm, với chỉ số bắt đầu từ $1$. Ví dụ, trung vị của $(1,3,2)$ là $2$, còn trung vị của $(1,3,2,4)$ là $3$.

Cho dãy $A$ gồm $N$ số nguyên. Với mỗi cặp $1\le L\le R\le N$, lấy trung vị của dãy con liên tiếp $A_L,A_{L+1},\ldots,A_R$ và đưa vào dãy $B$. Mỗi cặp chỉ số đóng góp một phần tử, kể cả khi nhiều trung vị bằng nhau. Hãy tìm trung vị của $B$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In giá trị trung vị của dãy $B$.

### Ràng buộc

- $1\le N\le10^5$.
- $1\le A_i\le10^9$.

### Sample Input 1

```text
3
1 3 2
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
1
5
```

### Sample Output 2

```text
5
```

### Sample Input 3

```text
10
1 10 2 8 3 7 4 6 5 9
```

### Sample Output 3

```text
6
```

### Giải thích

Ở ví dụ 1, sáu dãy con có các trung vị $1,3,2,3,3,2$. Sau khi sắp xếp, $B=(1,2,2,3,3,3)$; trung vị ở vị trí $4$ bằng $3$. Ở ví dụ 2, chỉ có một dãy con. Ví dụ 3 có trung vị của $B$ bằng $6$.
