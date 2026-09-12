Công ty X chuyên sản xuất các sản phẩm theo dây chuyền. Các sản phẩm khi đưa lên băng chuyền để hoàn thiện các công đoạn cuối sẽ được gắn một mã hàng để quản lí. Mã hàng của mỗi sản phẩm là một số tự nhiên chính là thứ tự của sản phẩm đó khi đưa lên băng chuyền. \
Do chưa kịp bảo dưỡng nên có hai công đoạn trên băng chuyên này không đảm bảo kỹ thuật. Trong đó, công đoạn thứ nhất cứ thực hiện trên $a$ sản phẩm lại có một sản phân bị lỗi, công đoạn thứ 2 cứ thực hiện trên $b$ sản phân lại có một sản phẩm bị lỗi. Vi vậy những sản phẩm có mã hàng chia hết cho $a$ hoặc chia hết cho $b$ đều bị lỗi nên hệ thống tự động loại ra các sản phẩm đó. Trong quá trình làm việc nhân viên trực ca muốn biết mã hàng của sản phẩm hoàn chỉnh đảm bảo chất lượng thứ $N$ là bao nhiêu để theo dõi, giám sát.

### Dữ liệu vào

Gồm một dòng chứa số 3 số nguyên dương $a, b, N$
ngăn cách nhau bởi dấu cách $(2 ≤ a, b ≤ 10^9; 2≤ N≤ 10^{18})$.

### Dữ liệu ra

Gồm một số nguyên duy nhất chứa mã số của sản phẩm thứ $N$ cần tìm.

### Giới hạn

- $70\%$ số test có $2\le N\le 10^6$.
- $30\%$ số test có $10^6 < N \le 10^{18}$.

### Sample Input

```
2 5 10
```

### Sample Output

```
23
```

### Giải thích

Các sản phẩm hoàn chỉnh có mã số lần lượt là: $1, 3, 7, 9, 11, 13, 17, 19, 21, 23, ...$ \
Vậy mã sản phẩm thứ $10$ có mã số $23$