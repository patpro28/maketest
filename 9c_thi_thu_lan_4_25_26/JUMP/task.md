### Đề bài

Bin và Bon là hai anh em sinh đôi, Bin là anh còn Bon là em. Sau một vụ tai nạn, Bin bị đau một chân. Anh ấy không biết làm gì hơn ngoài việc ngồi chơi Tetris. Hôm đó, Bon đã nghĩ ra một trò chơi đó là nhảy lò cò vượt chướng ngại vật, rất may mắn Bin vẫn còn một chân lành lặn nên anh ấy có thể tham gia.

Trò chơi được chơi trên $N$ bậc đánh số từ $1$ đến $N$, bậc thứ $i$ có độ cao $D_i$.

Nhiệm vụ của người chơi là nhảy từ bậc $1$ đến bậc $N$. Do còn bị đau, cho nên mỗi bước, Bin chỉ có thể nhảy từ bậc $i$ đến một trong các bậc $i+1, i+2, \ldots, i+K$ với $K$ là mức sức khoẻ hiện tại của Bin.

Một bước nhảy từ bậc $i$ đến bậc $j$ ($i < j$) được gọi là **mất sức** nếu như $D_i \le D_j$.

Bin rất tinh quái nên anh ấy muốn tìm cách nhảy về đích mà tốn ít lần mất sức nhất.

Bạn hãy giúp Bin tính toán số lần mất sức ít nhất mà Bin cần để về được đích.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N, K$ — số bậc và mức sức khỏe của Bin.
- Dòng thứ hai chứa $N$ số nguyên $D_1, D_2, \ldots, D_N$ — độ cao của các bậc.

### Dữ liệu ra

In ra số lần nhảy mất sức ít nhất để Bin nhảy về được đích.

### Rằng buộc

- $1 \le K < N \le 10^6$
- $1 \le D_i \le 10^9$

### Sample Input 1

    10 2
    3 10 5 3 1 3 2 6 3 4

### Sample Output 1

    3

### Giải thích

Một cách nhảy tối ưu là:

$$1 \rightarrow 2 \rightarrow 4 \rightarrow 6 \rightarrow 8 \rightarrow 10$$

Trong lộ trình này có tổng cộng $3$ lần nhảy mất sức.