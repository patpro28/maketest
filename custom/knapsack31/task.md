# KNAPSACK31 — Phá khiên trong đúng K lượt

### Đề bài

Có $N$ loại phép thuật. Một lần sử dụng phép loại $i$ tốn $C_i$ năng lượng và gây $D_i$ sát thương. Mỗi loại phép được sử dụng không giới hạn số lần.

Quái vật có lớp khiên cần nhận **ít nhất** $X$ sát thương để bị phá. Bạn phải sử dụng phép thuật **đúng $K$ lần**, mỗi lần chọn một loại phép. Không được bỏ lượt hoặc dừng lại trước khi dùng đủ $K$ lần, kể cả khi tổng sát thương đã đạt hoặc vượt $X$.

Hãy tìm tổng năng lượng ít nhất để gây ít nhất $X$ sát thương sau đúng $K$ lần sử dụng phép. Nếu không có cách thực hiện, hãy báo không thể.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,K,X$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $C_i,D_i$.

### Dữ liệu ra

In tổng năng lượng ít nhất của một phương án hợp lệ; in `-1` nếu không có phương án như vậy.

### Ràng buộc

- $1\le N\le50$.
- $1\le K\le200$; $1\le X\le2000$.
- $1\le C_i,D_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
1 3 10
2 10
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
2 3 16
1 3
4 10
```

### Sample Output 2

```text
6
```

### Sample Input 3

```text
1 2 10
3 4
```

### Sample Output 3

```text
-1
```

### Giải thích

Ở ví dụ 1, phải dùng phép duy nhất ba lần. Tổng sát thương là $30$, tổng năng lượng là $6$. Dù chỉ cần một lần dùng phép để phá khiên, không được dừng trước khi thực hiện đủ ba lần.

Ở ví dụ 2, dùng phép loại thứ nhất hai lần và phép loại thứ hai một lần: tổng sát thương $3+3+10=16$, tổng năng lượng $1+1+4=6$. Không thể chỉ dùng hai phép loại thứ hai rồi dừng, vì như vậy chưa đủ ba lần sử dụng.

Ở ví dụ 3, dùng phép duy nhất đúng hai lần chỉ gây $8$ sát thương, nhỏ hơn $10$. Dùng lần thứ ba sẽ vi phạm yêu cầu đúng hai lần, nên không có phương án hợp lệ.
