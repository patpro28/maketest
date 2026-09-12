Một công ty vận tải là khách hàng thường xuyên của công ty kinh doanh nhiên liệu. Công ty kinh doanh nhiên liệu đã công bố giá bán nhiên liệu của $N$ ngày sắp tới là dãy giá trị $a_1, a_2, .., a_n$. Vì là khách hàng quen nên công ty vận tải được công ty kinh doanh nhiên liệu cho chính sách ưu đãi đặc biệt, như sau: *Giá bán nhiên liệu ngày thứ $i$ không lớn hơn giá bán các ngày trước đó*. Như vậy nếu giá bán công bố ngày thứ $i$ là $a_i$, mà lớn hơn giá đã mua ở ngày thứ $i-1$ thì công ty vận tải sẽ được mua nhiên liệu ở ngày thứ $i$ với giá đã mua ở ngày thứ $i-1$

Để ước tính chi phí hoạt động, công ty vận tải đã đưa ra $q$ truy vấn có dạng $L, R, x$ có nghĩa là: Trong đoạn các ngày từ ngày thứ $L$ đến ngày thứ $R$ có bao nhiêu ngày được mua nhiên liệu với giá ưu đãi bằng $x$.

Em hãy lập trình giúp công ty vận tải trả lời $q$ truy vấn này.

### Dữ liệu vào

- Dòng 1: Số nguyên $N$ $(1\le N\le 2\times10^5)$.
- Dòng 2: $N$ số nguyên $a_1,a_2,...,a_n$ $(1\le a_i\le 10^6)$.
- Dòng 3: Số nguyên $q$ $(1\le q\le 2\times10^5)$.
- $q$ dòng tiếp theo: ba số nguyên $L,R,x$ $(1\le L,R\le N)$.

### Dữ liệu ra

Gồm $q$ dòng, mỗi dòng là kết quả của một truy vấn.

### Giới hạn

- $70\%$ số test có $1\le N,q\le 10^3$.
- $30\%$ số test có $10^3 < N \le 2\times 10^5$.

### Sample Input

```
8
12 15 10 11 9 20 8 8
3
3 7 8
5 8 12
2 5 10
```

### Sample Output

```
1
0
2
```

### Giải thích

Dãy giá ban đầu: $a = [12, 15, 10, 11, 9, 20, 8, 8]$ \
Các truy vấn:

- $(3,7,8)\to$ Từ ngày thứ $3$ đến ngày thứ $7$ có $1$ ngày thứ $7$ mua với giá ưu đãi bằng $8$.
- $(5,8,12)\to$ Từ ngày thứ $5$ đến ngày thứ $8$ không có ngày nào mua với giá ưu đãi bằng $12$.
- $(2,5,10)\to$ Từ ngày thứ $2$ đến ngày thứ $5$ có $2$ ngày thứ $3$ và ngày thứ $4$ mua với giá ưu đãi bằng $10$.
