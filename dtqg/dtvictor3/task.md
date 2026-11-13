# DTVICTOR3 — Lính canh của Victor III

### Đề bài

Victor sống ở thành phố $1$. Mạng lưới có $N$ thành phố đánh số từ $1$ đến $N$ và $N-1$ con đường hai chiều tạo thành một cây.

Victor thuê $K$ lính canh đánh số từ $1$ đến $K$. Mỗi thành phố được giao cho đúng một lính canh. Một lính canh có thể phụ trách nhiều thành phố hoặc không phụ trách thành phố nào, nhưng tại một thời điểm chỉ có thể có mặt ở một thành phố.

Một lính canh có thể tiếp viện cho thành phố $u$ nếu $u$ nằm trên đường đi từ ít nhất một thành phố do người lính đó phụ trách đến thành phố $1$, kể cả hai đầu mút. Mỗi lính canh chỉ được tính một lần, dù có thể xuất phát từ nhiều thành phố.

Trong $M$ phút tiếp theo, mỗi phút diễn ra đúng một sự kiện. Victor có thể đổi lính canh phụ trách một thành phố, hoặc quân kháng chiến có thể hỏi số lính canh lớn nhất có thể đến tiếp viện cho một thành phố. Mỗi lần hỏi dùng cách phân công tại thời điểm đó.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,K,M$.
- Dòng thứ hai chứa $N$ số nguyên $c_1,c_2,\ldots,c_N$, trong đó $c_i$ là mã lính canh ban đầu của thành phố $i$.
- Trong $N-1$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i,b_i$, cho biết có một con đường nối hai thành phố đó.
- Mỗi dòng trong $M$ dòng cuối mô tả một sự kiện theo thứ tự thời gian, thuộc một trong hai dạng sau.
  - `1 c k` giao thành phố $c$ cho lính canh $k$, thay cho lính canh hiện tại. Có thể $k$ chính là lính canh đang phụ trách $c$.
  - `2 u` yêu cầu đếm số lính canh lớn nhất có thể tiếp viện cho thành phố $u$.

### Dữ liệu ra

Với mỗi yêu cầu dạng `2 u`, in trên một dòng số lính canh lớn nhất có thể tiếp viện cho thành phố $u$. In các đáp án theo thứ tự yêu cầu.

### Ràng buộc

- $1\le N\le 200000$, $1\le M\le 200000$.
- $1\le K\le N$, $1\le c_i\le K$ với mọi $i$.
- $1\le a_i,b_i\le N$. Các con đường tạo thành một cây.
- $1\le u\le N$ với mỗi yêu cầu dạng `2 u`.
- $1\le c\le N$ và $1\le k\le K$ với mỗi sự kiện dạng `1 c k`.

### Sample Input 1

```text
5 5 5
3 4 1 1 2
1 2
1 3
2 4
2 5
2 2
2 1
1 2 1
2 2
2 1
```

### Sample Output 1

```text
3
4
2
3
```

### Sample Input 2

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

### Sample Output 2

```text
4
4
1
1
```

### Giải thích

Ở ví dụ 1, trước khi đổi lính canh, thành phố $2$ có thể nhận tiếp viện từ các lính canh $1,2,4$ và thành phố $1$ có thể nhận thêm lính canh $3$. Sau khi giao thành phố $2$ cho lính canh $1$, lính canh $4$ không còn phụ trách thành phố nào. Hai đáp án tiếp theo lần lượt là $2$ và $3$.

Ở ví dụ 2, xét các yêu cầu theo thứ tự. Tại thành phố $4$, các lính canh $1,2,3,4$ đều có thể tiếp viện. Tại thành phố $1$, vẫn có đúng bốn người đó vì lính canh $5$ không được giao thành phố nào. Thành phố $2$ và thành phố $7$ đều là lá, nên mỗi thành phố chỉ có một lính canh có thể tiếp viện.

### Nguồn

DMOPC '20 Contest 1 P5 — Victor Takes Over Canada, phiên bản ứng với subtask 3 của đề gốc.
