### Đề bài

Bạn đang giám sát trò chơi Hot and Cold diễn ra trên một cây vô hướng có $N$ đỉnh (đánh số từ $1$ đến $N$). Có $Q$ người chơi (seeker), mỗi người chơi thực hiện trò chơi độc lập.

Mỗi seeker được mô tả bởi ba số nguyên $S$, $T$ và $C$:

- Mục tiêu (target) là đỉnh $C$.
- Seeker sẽ đi trên đường đi đơn giữa $S$ và $T$.
- Tại mỗi đỉnh trên đường đi này, seeker hỏi “Hot or Cold?”, và bạn trả lời bằng **khoảng cách từ đỉnh đó đến $C$**.

Sau khi xử lý toàn bộ $Q$ seeker, với mỗi đỉnh $v$, bạn cần tính tổng tất cả các câu trả lời mà bạn đã đưa ra khi một seeker hỏi về đỉnh $v$. Nếu không có seeker nào hỏi về $v$, tổng bằng $0$.

Hãy in ra $N$ số nguyên: số thứ $v$ là tổng câu trả lời ứng với đỉnh $v$.

### Dữ liệu vào

- Dòng 1: hai số nguyên $N$, $Q$.
- $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u, v$, biểu thị có cạnh nối $u$ và $v$.
- $Q$ dòng tiếp theo, mỗi dòng gồm ba số nguyên $S, T, C$ mô tả một seeker.

### Dữ liệu ra

- In ra $N$ số nguyên: tổng giá trị câu trả lời tại mỗi đỉnh từ $1$ đến $N$.

### Ràng buộc

- $1 \le N, Q \le 10^5$
- $1 \le u, v, S, T, C \le N$
- $S, T, C$ đôi một phân biệt trong mỗi truy vấn
- Cây là vô hướng, không trọng số

### Sample Input 1
    5 3
    1 2
    2 3
    2 4
    1 5
    3 5 1
    5 4 1
    2 4 1

### Sample Output 1
    0 3 2 4 2

### Sample Input 2
    6 2
    3 4
    2 5
    6 4
    5 4
    1 2
    6 2 6
    5 1 2

### Sample Output 2
    1 3 0 1 3 0