# DTESPORT — Thể thao điện tử

### Đề bài

Trò chơi có $N$ nhiệm vụ, đánh số từ $1$ đến $N$. Nhiệm vụ $i$ có độ khó $D_i$. Hoangcoder thay đổi độ khó và truy vấn theo ba thao tác.

- `1 L R S C` (patch) cộng $S+(i-L)C$ vào $D_i$ với mọi $L\le i\le R$.
- `2 L R S C` (rewrite) gán $D_i=S+(i-L)C$ với mọi $L\le i\le R$.
- `3 L R` (evaluate) tìm độ dài lớn nhất của một đoạn nhiệm vụ thú vị nằm hoàn toàn trong $[L,R]$.

Đoạn $[a,b]$ là thú vị nếu $D_{i+1}-D_i$ có cùng giá trị với mọi $a\le i<b$. Giá trị chung có thể âm, bằng $0$ hoặc dương. Một nhiệm vụ đứng riêng là một đoạn thú vị có độ dài $1$.

### Dữ liệu vào

Đọc dữ liệu từ tệp `ESPORT.INP`.

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác dưới một trong ba dạng trên. Thực hiện các thao tác theo thứ tự xuất hiện.

### Dữ liệu ra

Ghi vào tệp `ESPORT.OUT` một dòng cho mỗi thao tác loại $3$. Mỗi dòng chứa độ dài lớn nhất tìm được cho thao tác tương ứng.

### Ràng buộc

- $1\le N,Q\le3\cdot10^5$.
- $|D_i|\le10^6$ với mọi độ khó ban đầu.
- $1\le L\le R\le N$ với mọi thao tác.
- $|S|,|C|\le10^6$ với thao tác loại $1$ và $2$.

### Sample Input 1

```text
10 6
1 2 3 4 1 2 3 4 5 5
3 1 10
1 1 4 -1 -1
3 1 10
3 9 10
2 5 10 -2 -2
3 1 10
```

### Sample Output 1

```text
5
6
2
7
```

### Sample Input 2

```text
10 5
1 2 3 4 1 2 3 4 5 5
3 1 10
1 1 10 1 2
3 1 10
2 1 10 3 4
3 1 10
```

### Sample Output 2

```text
5
5
10
```

### Sample Input 3

```text
10 5
1 2 3 4 1 2 3 4 5 5
2 10 10 6 1
3 5 10
1 5 5 4 1
3 1 5
3 1 6
```

### Sample Output 3

```text
6
5
5
```

### Sample Input 4

```text
10 5
1 2 3 4 1 2 3 4 5 5
1 1 4 -1 -1
3 1 5
3 4 5
1 5 10 -1 -1
3 1 10
```

### Sample Output 4

```text
4
2
9
```

### Giải thích

- Ví dụ 1. Ban đầu đoạn $[5,9]$ có công sai $1$ và độ dài $5$. Sau thao tác patch, đoạn $[4,9]$ có công sai $1$ và độ dài $6$, còn đoạn $[9,10]$ gồm hai giá trị $5$. Sau thao tác rewrite, đoạn $[4,10]$ có công sai $-2$ và độ dài $7$.
- Ví dụ 2. Thao tác patch cộng một cấp số cộng vào toàn dãy nên độ dài lớn nhất vẫn là $5$. Thao tác rewrite biến toàn bộ $10$ nhiệm vụ thành một cấp số cộng có công sai $4$.
- Ví dụ 3. Sau khi gán $D_{10}=6$, đoạn $[5,10]$ có độ dài $6$ và công sai $1$. Sau khi tăng $D_5$ thêm $4$, đoạn $[1,5]$ có độ dài $5$ và công sai $1$, còn đoạn $[1,6]$ có cùng đoạn thú vị dài nhất.
- Ví dụ 4. Sau thao tác patch đầu tiên, bốn phần tử đầu bằng $0$ và đoạn $[4,5]$ có độ dài $2$. Thao tác patch tiếp theo đưa các phần tử từ $5$ đến $9$ về $0$, tạo đoạn thú vị $[1,9]$.
