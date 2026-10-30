# DTCANBANG — Điểm tập kết tối ưu

### Đề bài

Cho một cây có $N$ đỉnh, đặt gốc tại đỉnh $1$. Đỉnh $v$ có tọa độ nguyên $A_v$ và trọng số dương $W_v$. Tọa độ này là một giá trị gắn với đỉnh, không phải khoảng cách trên cây. Cây con của một đỉnh gồm chính đỉnh đó và mọi hậu duệ của nó.

Với mỗi đỉnh $u$, bạn được chọn riêng một số nguyên $X$. Chi phí của cây con $u$ tại $X$ là

$$\sum_{v\in subtree(u)} W_v|A_v-X|.$$

Hãy tìm chi phí nhỏ nhất cho từng cây con. Các cây con được tối ưu độc lập; không cần dùng chung một giá trị $X$. Chỉ cần in chi phí, không cần in vị trí $X$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $v$ chứa hai số nguyên $A_v,W_v$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh hai chiều của cây.

### Dữ liệu ra

In $N$ dòng. Dòng thứ $u$ chứa chi phí nhỏ nhất của cây con $u$. Không lấy phần dư theo modulo.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $0\le A_v\le10^9$.
- $1\le W_v\le1000$.
- Mọi chỉ số đỉnh của cạnh thuộc đoạn $[1,N]$; các cạnh tạo thành một cây.
- Kết quả không vượt $2\cdot10^{17}$; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
5
0 1
10 1
20 1
30 1
40 1
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
60
0
20
0
0
```

### Sample Input 2

```text
3
0 10
100 1
100 1
1 2
1 3
```

### Sample Output 2

```text
200
0
0
```

### Sample Input 3

```text
2
0 1
1000000000 1
1 2
```

### Sample Output 3

```text
1000000000
0
```

### Giải thích

Ở ví dụ 1, với cả cây chọn $X=20$ cho chi phí $20+10+0+10+20=60$. Với cây con $3$, chọn $X=30$ cho chi phí $10+0+10=20$.

Ở ví dụ 2, chọn $X=0$ cho chi phí $10\cdot0+100+100=200$. Trọng số làm cho đỉnh ở tọa độ $0$ có ảnh hưởng lớn hơn hai đỉnh còn lại.

Ở ví dụ 3, mọi số nguyên $X$ từ $0$ tới $10^9$ đều cho cùng chi phí $10^9$ đối với cả cây. Một cây con chỉ có một đỉnh luôn có chi phí nhỏ nhất bằng $0$.
