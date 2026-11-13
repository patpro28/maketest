# DTVICTOR2 — Lính canh của Victor II

### Đề bài

Victor sống ở thành phố $1$. Mạng lưới có $N$ thành phố đánh số từ $1$ đến $N$ và $N-1$ con đường hai chiều tạo thành một cây.

Victor thuê $K$ lính canh đánh số từ $1$ đến $K$. Mỗi thành phố được giao cho đúng một lính canh. Một lính canh có thể phụ trách nhiều thành phố hoặc không phụ trách thành phố nào, nhưng tại một thời điểm chỉ có thể có mặt ở một thành phố.

Một lính canh có thể tiếp viện cho thành phố $u$ nếu $u$ nằm trên đường đi từ ít nhất một thành phố do người lính đó phụ trách đến thành phố $1$, kể cả hai đầu mút. Mỗi lính canh chỉ được tính một lần, dù có thể xuất phát từ nhiều thành phố.

Việc phân công được giữ cố định. Có $M$ yêu cầu. Với mỗi yêu cầu, hãy tìm số lính canh lớn nhất có thể đến tiếp viện cho thành phố được hỏi.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,K,M$.
- Dòng thứ hai chứa $N$ số nguyên $c_1,c_2,\ldots,c_N$, trong đó $c_i$ là mã lính canh ban đầu của thành phố $i$.
- Trong $N-1$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i,b_i$, cho biết có một con đường nối hai thành phố đó.
- Mỗi dòng trong $M$ dòng cuối có dạng `2 u`, yêu cầu đếm số lính canh lớn nhất có thể tiếp viện cho thành phố $u$.

### Dữ liệu ra

Với mỗi yêu cầu dạng `2 u`, in trên một dòng số lính canh lớn nhất có thể tiếp viện cho thành phố $u$. In các đáp án theo thứ tự yêu cầu.

### Ràng buộc

- $1\le N\le 200000$, $1\le M\le 200000$.
- $1\le K\le N$, $1\le c_i\le K$ với mọi $i$.
- $1\le a_i,b_i\le N$. Các con đường tạo thành một cây.
- $1\le u\le N$ với mỗi yêu cầu dạng `2 u`.
- Mọi yêu cầu đều có dạng `2 u`.

### Sample Input 1

```text
7 5 4
1 2 3 4 3 2 1
1 2
1 3
1 4
4 5
4 6
4 7
2 4
2 1
2 2
2 7
```

### Sample Output 1

```text
4
4
1
1
```

### Sample Input 2

```text
4 4 3
2 2 2 2
1 3
3 2
2 4
2 1
2 3
2 4
```

### Sample Output 2

```text
1
1
1
```

### Giải thích

Ở ví dụ 1, xét các yêu cầu theo thứ tự. Tại thành phố $4$, các lính canh $1,2,3,4$ đều có thể tiếp viện. Tại thành phố $1$, vẫn có đúng bốn người đó vì lính canh $5$ không được giao thành phố nào. Thành phố $2$ và thành phố $7$ đều là lá, nên mỗi thành phố chỉ có một lính canh có thể tiếp viện.

Ở ví dụ 2, lính canh $2$ phụ trách cả bốn thành phố. Người này có thể tiếp viện cho từng thành phố được hỏi, nhưng chỉ được tính một lần trong mỗi yêu cầu.

### Nguồn

DMOPC '20 Contest 1 P5 — Victor Takes Over Canada, phiên bản ứng với subtask 2 của đề gốc.

Ví dụ 1 là ví dụ 2 của đề gốc. Ví dụ 2 được bổ sung cho phiên bản này.
