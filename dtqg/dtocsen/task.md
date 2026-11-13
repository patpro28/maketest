# DTOCSEN — Ốc sên

### Đề bài

Một con ốc sên bắt đầu ở đáy giếng, tại độ cao $0$. Miệng giếng ở độ cao $H$. Mỗi ngày, ốc sên lặp lại cùng một dãy $N$ bước. Nếu độ cao trước bước $i$ là $h$, độ cao sau bước đó là $\max(0,h+P_i)$. Nếu chưa ra khỏi giếng, ốc sên bắt đầu ngày tiếp theo tại độ cao nó đạt được sau bước cuối của ngày hiện tại.

Hãy xác định ngày và bước đầu tiên mà độ cao của ốc sên đạt ít nhất $H$. Ngày và bước đều được đánh số từ $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $H,N$.
- Dòng thứ hai chứa $N$ số nguyên $P_0,P_1,\ldots,P_{N-1}$ theo thứ tự thực hiện các bước.

### Dữ liệu ra

In hai số nguyên $x,y$ cách nhau bởi một dấu cách, lần lượt là ngày và bước mà ốc sên ra khỏi giếng. Nếu ốc sên không thể ra khỏi giếng, in `-1 -1`.

### Ràng buộc

- $1\le H\le 10^{12}$.
- $1\le N\le 10^4$.
- $-10^{12}\le P_i\le 10^{12}$ với mọi $0\le i<N$.

### Sample Input 1

```text
3 1
1
```

### Sample Output 1

```text
2 0
```

### Sample Input 2

```text
5 1
-1
```

### Sample Output 2

```text
-1 -1
```

### Sample Input 3

```text
5 2
4 -2
```

### Sample Output 3

```text
1 0
```

### Sample Input 4

```text
5 5
1 1 1 -10 2
```

### Sample Output 4

```text
1 2
```

### Giải thích

- Ví dụ 1. Mỗi ngày ốc sên lên thêm $1$, nên đạt độ cao $3$ ở bước $0$ của ngày $2$.
- Ví dụ 2. Sau mỗi bước, ốc sên vẫn ở độ cao $0$.
- Ví dụ 3. Ngày $0$ kết thúc ở độ cao $2$. Bước $0$ của ngày $1$ đưa ốc sên lên độ cao $6$.
- Ví dụ 4. Ngày $0$ kết thúc ở độ cao $2$. Ba bước đầu ngày $1$ đưa ốc sên lần lượt lên độ cao $3,4,5$.
