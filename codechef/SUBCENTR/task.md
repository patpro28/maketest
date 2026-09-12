### Đề bài

Cho một cây gồm $N$ điểm (được đánh số từ $1$ đến $N$) và $Q$ truy vấn (được đánh số từ $1$ đến $Q$). Đối với mọi $i$, trong truy vấn thứ $i$, cho $K_i$ điểm $x_1, x_2, \ldots, x_{K_i}$. Xét cây con nhỏ nhất chứa tất cả các điểm này; bạn hãy tìm tất cả các **tâm** của cây con này.

Một điểm được gọi là **tâm** của cây nếu nó nằm ở **giữa** ít nhất một đường đi dài nhất trong cây đó. Lưu ý rằng có thể có nhiều đường đi dài nhất (đường đi có cùng độ dài tối đa) và đối với đường đi dài nhất chứa số điểm chẵn, có hai điểm nằm ở giữa đường đi đó.

### Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $T$ - số test. Mỗi test được mô tả như sau:

- Dòng đầu tiên của mỗi test chứa hai số nguyên $N$ và $Q$.
- $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u$ và $v$ thể hiện một cạnh nối trên cây.
- $Q$ dòng tiếp theo, mỗi dòng bắt đầu bằng số $K$, tiếp theo là $K$ số nguyên $x_i$.

### Dữ liệu ra

- Với mỗi truy vấn, in ra một số $C$ thể hiện số tâm, tiếp sau đó là $C$ số nguyên là các điểm là tâm của cây con theo thứ tự tăng dần.

### Rằng buộc

- $1 \le T, N \le 10^5$.
- $1 \le u, v \le N$.
- $1 \le Q \le 10^6$.
- Trong mỗi truy vấn, $x_i$ đôi một khác nhau.
- Tổng $N$ trong tất cả test không vượt quá $5\times 10^5$.
- Tổng $Q$ trong tất cả test không vượt quá $10^6$.
- Tổng $K$ trong tất cả truy vấn không vượt quá $10^6$.

### Sample Input

```
2
3 2
1 2
2 3
2 1 3
2 1 2
5 2
1 2
2 3
2 4
3 5
1 2
2 4 5
```

### Sample Output

```
1 2
2 1 2
1 2
2 2 3
```