# PREFIX081 — Vị trí đoạn dài nhất không vượt T

### Đề bài

Cho dãy $N$ số nguyên không âm $A_1,A_2,\ldots,A_N$, đánh số từ $1$.

Hãy chọn đoạn liên tiếp không rỗng có tổng không vượt quá $T$ và có độ dài lớn nhất. Nếu có nhiều đoạn cùng độ dài lớn nhất, chọn đoạn có vị trí bắt đầu nhỏ nhất. In độ dài và hai đầu mút của đoạn được chọn.

Độ dài đoạn được phép thay đổi. Chỉ xét đoạn không rỗng nằm hoàn toàn trong dãy, không nối vòng. Các đoạn được phép chồng lấn; hai đoạn khác nhau nếu có vị trí bắt đầu hoặc vị trí kết thúc khác nhau.

### Dữ liệu vào

- Dòng đầu chứa 2 số nguyên $N,T$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

Nếu tồn tại đoạn thỏa điều kiện, in ba số nguyên trên một dòng: độ dài lớn nhất, vị trí bắt đầu và vị trí kết thúc của đoạn được chọn. Nếu không có đoạn không rỗng nào thỏa điều kiện, in `0 0 0`.

### Ràng buộc

- $1\le N\le200000$.
- $0\le A_i\le10^9$.
- $0\le T\le2\cdot10^{14}$.

### Sample Input 1

```text
6 4
2 1 3 1 1 2
```

### Sample Output 1

```text
3 4 6
```

### Sample Input 2

```text
2 4
5 6
```

### Sample Output 2

```text
0 0 0
```

### Sample Input 3

```text
4 0
0 0 1 0
```

### Sample Output 3

```text
2 1 2
```

### Giải thích

Ở ví dụ 1: Đoạn $[4,6]$ có tổng $4$, độ dài $3$ là lớn nhất phù hợp; đây cũng là vị trí bắt đầu sớm nhất trong các đoạn cùng độ dài tối ưu.

Ở ví dụ 2: Không có đoạn không rỗng nào thỏa điều kiện.

Ở ví dụ 3: Đoạn $[1,2]$ có tổng $0$, độ dài $2$ là lớn nhất phù hợp; đây cũng là vị trí bắt đầu sớm nhất trong các đoạn cùng độ dài tối ưu.
