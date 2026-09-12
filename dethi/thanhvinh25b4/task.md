### Đề bài

Phố đi bộ đường HTM tổ chức trò chơi ghép đôi như sau: Mỗi người tham gia trò chơi ghép đôi sẽ được phát 1 vé có đánh số thứ tự từ $1,2,....N$. Trên mỗi vé của người chơi thứ $i$ chứa một số ngẫu nhiên $a_i$ là mã số của người tham gia. Kết thúc phần chơi, BTC sẽ chọn ra cặp đôi may mắn và trao thường. Cặp đôi may mắn là người chơi thứ $i$ và $j$ thỏa mãn điều kiện sau:

- $1\le i < j \le N$.
- $a_j - a_i \ge P$ với $P$ là số ngẫu nhiên do BTC đưa ra.
- $j - i$ lớn nhất.

### Yêu cầu

Hãy cho biết vị trí của cặp đôi may mắn.

### Dữ liệu vào

- Dòng thứ nhất chứa 2 số nguyên $N$ và $P$ $(1 \le N \le 10^6, 0 < P \le 10^6)$.
- Dòng thứ hai chứa $N$ số nguyên $a_1, a_2,...,a_N$ $(0 < a_i \le 10^9)$.

### Dữ liệu ra

Gồm hai số nguyên dương là vị trí của cặp đôi may mắn. Nếu có nhiều cặp đôi may mắn thỏa mãn yêu cầu bài toán thì đưa ra vị trí cặp đôi may mắn đâu tiên, nếu không có cặp đôi nào thì ghi kết quả bằng $0$. Các số trên một dòng cách nhau một dấu cách trống.

### Sample Input 1

```
7 3
4 3 7 2 6 4 5
```

### Sample Output 1

```
2 5
```

### Sample Input 2

```
10 7
18 18 10 2 1 18 15 18 9 8
```

### Sample Output 2

```
3 8
```

### Sample Input 3

```
7 3
1 2 2 2 3 3 3
```

### Sample Output 3

```
0
```