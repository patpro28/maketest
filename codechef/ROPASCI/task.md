### Đề bài

Có $N$ người chơi đứng thành một hàng, đánh số từ $1$ đến $N$ từ trái sang phải. Tất cả sẽ chơi trò chơi "Oẳn Tù Tì". Mỗi người chơi đã quyết định sẵn họ sẽ chơi gì, được cung cấp dưới dạng chuỗi $S$ có độ dài $N$, tức là:

- $S_i$ là 'R' nếu người chơi $i$ chơi "Rock" (Đá).
- $S_i$ là 'P' nếu người chơi $i$ chơi "Paper" (Giấy).
- $S_i$ là 'S' nếu người chơi $i$ chơi "Scissors" (Kéo).

Gọi $W(i, j)$ là nước đi của người thắng khi các người chơi từ $i, i+1, ..., j$ đấu với nhau theo thứ tự từ trái sang phải như sau:

- Trước tiên, người chơi $i$ đấu với người chơi $i+1$.
- Người thắng trong trận này sẽ đấu với người chơi $i+2$.
- Người thắng trong trận này sẽ tiếp tục đấu với người chơi $i+3$.
- ...
- Người thắng cuối cùng sau $j - i$ trận sẽ được xác định là người thắng toàn bộ và $W(i, j)$ là nước đi của người đó.

Nếu $i = j$, người chơi $i$ được xem là người thắng và $W(i, i) = S_i$.

Nhiệm vụ của bạn là tính giá trị của $W(i, N)$ với mọi $i$ từ $1$ đến $N$.

**Lưu ý**:

Khi hai người chơi ở vị trí $i$ và $j$ ($i < j$) đấu với nhau:

- Nếu $S_i \ne S_j$, người thắng được xác định bởi luật cổ điển: Rock thắng Scissors, Scissors thắng Paper, Paper thắng Rock.
- Nếu $S_i = S_j$, người có chỉ số nhỏ hơn (tức là $i$) sẽ thắng.

### Dữ liệu vào

- Dòng đầu tiên chứa số nguyên $T$ — số lượng bộ test.
- Mỗi bộ test gồm:
    - Một dòng chứa số nguyên $N$ — số lượng người chơi.
    - Một dòng chứa chuỗi $S$ gồm $N$ ký tự biểu diễn nước đi của các người chơi.

### Dữ liệu ra

Với mỗi test, in ra một chuỗi gồm $N$ ký tự, trong đó ký tự thứ $i$ là $W(i, N)$.

### Giới hạn

- $1\le T\le 10^5$.
- $1\le N\le 5\times 10^5$
- Tổng của $N$ trong tất cả các test không vượt quá $5\times 10^5$.

### Sample Input

    2
    1
    S
    4
    SSPR

### Sample Output

    S
    RRPR

### Giải thích

- Test đầu tiên: Chỉ có một người do đó $W(1,1)=S$.
- Test thứ hai:
    - $W(1,4)$ được tính như sau: Người 1 chơi với người 2, người 1 thắng; Người 1 chơi với người 3, người 1 thắng; Người 1 chơi với người 4, người 4 thắng. Do đó $W(1,4)=R$.
    - $W(3,4)$ được tính như sau: Người 3 chơi với người 4, người 3 thắng. Do đó $W(3,4)=P$.