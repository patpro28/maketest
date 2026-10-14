# Task 1 (Level C)

### Đề bài

Tony có $n$ lá bài, trên mỗi lá bài có ghi một số nguyên dương $x_i$. Anh ấy muốn chọn một số lá bài (ít nhất một lá) trong $n$ lá bài đó sao cho trung bình cộng của các số được ghi trên những lá bài được chọn đúng bằng $A$.
Hãy cho biết có bao nhiêu cách khác nhau để chọn các lá bài như vậy.

### Dữ liệu vào

* Dòng đầu tiên chứa hai số nguyên dương $n, A$.
* Dòng thứ hai chứa $n$ số nguyên dương $x_i$ biểu diễn những số được viết trên các lá bài.

### Dữ liệu ra

* Ghi ra một số nguyên duy nhất là số lượng cách chọn các lá bài sao cho trung bình cộng của những số được ghi trên đó đúng bằng $A$.

### Rằng buộc

* $1 \le n \le 50$.
* $1 \le A \le 50$.
* $1 \le x_i \le 50$.

:::samples

:::sample
```input
3 2
1 2 3
```

```output
3
```

:::

:::


### Giải thích

Các cách chọn thỏa mãn:

* Chọn tập ${2}$: trung bình cộng là $2$.
* Chọn tập ${1,3}$: trung bình cộng là $\dfrac{1+3}{2} = 2$.
* Chọn tập ${1,2,3}$: trung bình cộng là $\dfrac{1+2+3}{3} = 2$.

Vì vậy có $3$ cách chọn.

# Task 2 (Level D)

Bạn có một mảng các số nguyên $a$ có kích thước $n$. Ban đầu, tất cả các phần tử của mảng đều bằng 1. Bạn có thể thực hiện thao tác sau: chọn hai số nguyên $i$ ($1 \leq i \leq n$) và $x$ ($x > 0$), sau đó tăng giá trị của $a_i$ lên $\left\lfloor \frac{a_i}{x} \right\rfloor$ (tức là làm cho $a_i = a_i + \left\lfloor \frac{a_i}{x} \right\rfloor$).

Sau khi thực hiện tất cả các thao tác, bạn sẽ nhận được $c_i$ đồng xu cho tất cả $i$ sao cho $a_i = b_i$.

Nhiệm vụ của bạn là xác định số đồng xu tối đa mà bạn có thể nhận được bằng cách thực hiện không quá $k$ thao tác.

### Đầu vào

Dòng đầu tiên chứa một số nguyên $t$ ($1 \leq t \leq 100$) - số lượng test case.

Dòng đầu tiên của mỗi test case chứa hai số nguyên $n$ và $k$ ($1 \leq n \leq 10^3$; $0 \leq k \leq 10^6$) - kích thước của mảng và số lượng thao tác tối đa, tương ứng.

Dòng thứ hai chứa $n$ số nguyên $b_1, b_2, \ldots, b_n$ ($1 \leq b_i \leq 10^3$).

Dòng thứ ba chứa $n$ số nguyên $c_1, c_2, \ldots, c_n$ ($1 \leq c_i \leq 10^6$).

Tổng số $n$ trong tất cả các test case không vượt quá $10^3$.

### Đầu ra

Đối với mỗi test case, in ra một số nguyên - số đồng xu tối đa mà bạn có thể nhận được bằng cách thực hiện không quá $k$ thao tác.

:::samples

:::sample
```input
3
3 3
2 999 2
12 7 12
4 4
1 7 5 2
2 6 5 2
10 1000000
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10
```

```output
24
9
55
```

:::

:::

# Task 3 (Level D)

### Đề bài

Xét một dãy số nguyên dương gồm $N$ phần tử $A_1, A_2, \dots, A_N$.

Từ dãy $A$, tạo dãy $B_1, B_2, \dots, B_N$ theo quy tắc:

- $B_i = A_i - 1$ nếu $A_i$ là số chẵn.
- $B_i = A_i + 1$ nếu $A_i$ là số lẻ.

Sau đó tạo dãy $C_1, C_2, \dots, C_{2N}$ bằng cách **gộp** hai dãy $A$ và $B$ lại, rồi **sắp xếp lại theo thứ tự không giảm**.

### Yêu cầu

Cho trước dãy $C_1, C_2, \dots, C_{2N}$ và một số nguyên dương $K$. Hãy **đếm số lượng dãy $A_1, A_2, \dots, A_N$** thỏa mãn các điều kiện sau:

- $A_1 \leq A_2 \leq \dots \leq A_N$
- $A_1 + A_2 + \dots + A_N = K$
- Từ dãy $A$ có thể tạo ra dãy $C$ như mô tả ở trên

### Dữ liệu vào

- Dòng đầu tiên: số nguyên $T$ ($1 \leq T \leq 5$) — số test
- Với mỗi test:
      - Dòng 1: hai số nguyên $N$ và $K$  
        ($1 \leq N \leq 10^3$, $1 \leq K \leq 2 \cdot 10^6$)
      - Dòng 2: $2N$ số nguyên $C_1, C_2, \dots, C_{2N}$  
    ($1 \leq C_i \leq 2000$)

### Dữ liệu ra

- In ra một số nguyên duy nhất là **số lượng dãy $A_1, A_2, ..., A_N$** thỏa mãn yêu cầu.
- Vì kết quả có thể rất lớn, in ra **kết quả chia dư cho $10^9 + 7$**.

:::samples

:::sample
```input
2
2 4
1 2 3 4
2 5
1 2 3 4
```

```output
1
2
```

:::

:::


### Giải thích

- **Test 1**: Có duy nhất một dãy thỏa mãn là $A = [1, 3]$
- **Test 2**: Có hai dãy thỏa mãn là $A = [1, 4]$ và $A = [2, 3]$

### Giới hạn

- **Subtask 1** (10% số test): $C_i \leq 2$
- **Subtask 2** (20% số test): $N \leq 8$ và $C_i \leq 10$
- **Subtask 3** (20% số test): $N \leq 10^2$ và $C_i \leq 100$
- **Subtask 4** (50% số test): $N \leq 10^3$

# Task 4 (Level E)

### Đề bài

Cho một số nguyên dương $N$.

Một mảng $A$ được gọi là **tốt** nếu thỏa mãn tất cả các điều kiện sau:

1. $1 \le A_i \le N$ với mọi $1 \le i \le |A|$
2. $A_i \le A_{i+1}$ với mọi $1 \le i < |A|$ (tức là dãy không giảm)
3. $A_1 + A_2 + \dots + A_{|A|} = N$
4. $A_1 \times A_2 \times \dots \times A_{|A|} = N$

Trong đó $|A|$ là độ dài mảng $A$.

Gọi $R$ là số lượng mảng tốt. Hãy tìm $R$. Có thể chứng minh rằng đáp án không vượt quá $10^{18}$.

Ví dụ, với $N = 6$ thì $R = 2$ vì có đúng $2$ mảng tốt là $[6]$ và $[1, 2, 3]$.

### Dữ liệu vào

* Dòng đầu chứa một số nguyên $T$ — số lượng test.
* Mỗi test gồm một dòng chứa một số nguyên $N$.

### Dữ liệu ra

Với mỗi test, in ra trên một dòng một số nguyên $R$ — số lượng mảng tốt tương ứng với $N$.

### Ràng buộc

* $1 \le T \le 20$
* $1 \le N \le 10^9$

:::samples

:::sample
```input
11
1
2
3
4
5
6
7
8
9
10
1000000
```

```output
1
1
1
2
1
2
1
3
2
2
1043
```

:::

:::


### Giải thích

* Với $N = 1$: chỉ có mảng $[1]$ thỏa mãn nên $R = 1$.
* Với $N = 6$: có hai mảng tốt là $[6]$ và $[1, 2, 3]$ nên $R = 2$.
* Các giá trị khác của $N$ được tính tương tự theo định nghĩa mảng tốt.

# Task 5 (Level C)

## KNAPSACK15 — Xây số lớn nhất

### Đề bài

Bạn có đúng $N$ đồng. Viết một chữ số $d$ tốn $C_d$ đồng, với $d=0,1,\ldots,9$. Mỗi chữ số có thể được viết nhiều lần.

Hãy tạo một số nguyên không âm lớn nhất bằng cách dùng **đúng** $N$ đồng. Biểu diễn phải có ít nhất một chữ số và không có chữ số $0$ ở đầu, ngoại trừ số $0$ được viết bằng đúng một chữ số.

Nếu không thể viết một số hợp lệ với đúng số tiền đang có, hãy báo không thể.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa mười số nguyên $C_0,C_1,\ldots,C_9$ theo thứ tự chữ số.

### Dữ liệu ra

In số nguyên lớn nhất dưới dạng một chuỗi chữ số; in `-1` nếu không tồn tại số hợp lệ.

### Ràng buộc

- $1\le N\le10000$.
- $1\le C_d\le10000$ với mọi $0\le d\le9$.
- Đáp án có thể rất dài; không yêu cầu lưu đáp án trong kiểu số nguyên. Các chữ số được dùng không giới hạn số lần.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $C_0=C_1=\cdots=C_9$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
1 2 3 4 5 6 7 8 9 10
```

### Sample Output 1

```text
1000
```

### Sample Input 2

```text
3
2 2 2 2 2 2 2 2 2 2
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, viết $1000$ tốn $2+1+1+1=5$ đồng. Không thể viết số hợp lệ có năm chữ số vì chữ số khác $0$ rẻ nhất tốn $2$ đồng. Ở ví dụ 2, mọi số đều có chi phí chẵn.
