# NET2LINE — Kết nối hai hàng máy tính

Cho $2n$ máy tính đánh số từ $1$ đến $2n$, xếp thành hai hàng, mỗi hàng $n$ máy:

```text
  1 --- 2 --- ... --- n
  |     |             |
 n+1 -- n+2 -- ... --- 2n
```

Các kết nối có thể thuê gồm:

- Máy tính $i$ nối với máy tính $i+1$, chi phí $u_i$, với $1 \le i < n$.
- Máy tính $n+i$ nối với máy tính $n+i+1$, chi phí $v_i$, với $1 \le i < n$.
- Máy tính $i$ nối với máy tính $n+i$, chi phí $w_i$, với $1 \le i \le n$.

Mỗi kết nối là hai chiều và chỉ được chọn tối đa một lần. Một phương án thuê đường truyền là một tập các kết nối sao cho tất cả $2n$ máy tính liên thông với nhau và tổng chi phí là số chẵn. Phương án được phép chứa chu trình.

Hãy tìm tổng chi phí nhỏ nhất của một phương án như vậy.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ ($1 \le T \le 20$), là số bộ dữ liệu.
Mỗi bộ dữ liệu gồm bốn dòng:

- Dòng thứ nhất chứa số nguyên $n$ ($1 \le n \le 10^5$).
- Dòng thứ hai chứa $n-1$ số nguyên $u_1,u_2,\ldots,u_{n-1}$.
- Dòng thứ ba chứa $n-1$ số nguyên $v_1,v_2,\ldots,v_{n-1}$.
- Dòng thứ tư chứa $n$ số nguyên $w_1,w_2,\ldots,w_n$.

Tất cả chi phí là số nguyên dương không vượt quá $10^4$.
Khi $n=1$, dòng thứ hai và dòng thứ ba là hai dòng trống.
Không có ràng buộc bổ sung về tổng $n$ của các bộ dữ liệu.

### Dữ liệu ra

In $T$ dòng. Dòng thứ $i$ chứa tổng chi phí nhỏ nhất cho bộ dữ liệu thứ $i$; in $-1$ nếu không có phương án thỏa mãn.

### Ràng buộc

| Nhóm | Tỉ lệ số test | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 25% | $n \le 5$ |
| 2 | 25% | Mọi chi phí đều chẵn |
| 3 | 25% | $n \le 1000$ |
| 4 | 25% | Không có ràng buộc bổ sung |

### Sample Input

```text
2
3
2 1
3 7
6 4 5
3
2 10
3 7
6 4 5
```

### Sample Output

```text
18
24
```
