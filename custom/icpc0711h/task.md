# ICPC0711H — Đổi chỗ quân bài

### Đề bài

Có $N$ quân bài. Quân bài thứ $i$ có số $A_i$ ở mặt trước và số $B_i$ ở mặt sau. Ban đầu, tất cả đều ngửa mặt trước.

Mỗi thao tác chọn $1\le i<N$, đổi chỗ hai quân bài ở vị trí $i$ và $i+1$, đồng thời lật cả hai quân bài này.

Hãy tìm số thao tác ít nhất để dãy số đang hiện trên các quân bài là không giảm. Dữ liệu bảo đảm tồn tại cách thực hiện.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\ldots,A_N$.
- Dòng thứ ba chứa $N$ số nguyên $B_1,\ldots,B_N$.

### Dữ liệu ra

In số thao tác ít nhất để dãy số hiện trên các quân bài không giảm.

### Ràng buộc

- $2\le N\le18$.
- $0\le A_i,B_i\le50$.
- Dữ liệu bảo đảm có lời giải.

### Sample Input 1

```text
3
3 4 3
3 2 5
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
3
1 2 3
4 5 6
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
5
3 26 17 8 23
13 12 18 17 27
```

### Sample Output 3

```text
2
```

### Giải thích

Ở ví dụ 1, đổi chỗ và lật hai quân bài đầu thu được $(2,3,3)$. Ở ví dụ 2, dãy đã không giảm. Ở ví dụ 3, thao tác tại vị trí $1$ rồi vị trí $3$ tạo ra lần lượt $(12,13,17,8,23)$ và $(12,13,17,18,23)$.
