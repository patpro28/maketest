# ICPC0711K — Dãy số TriSeq

### Đề bài

Ba số nguyên dương $x,y,z$ thỏa mãn bất đẳng thức tam giác nếu $x+y>z$, $y+z>x$ và $z+x>y$.

Một dãy số nguyên dương được gọi là **TriSeq** nếu các phần tử tại ba vị trí bất kỳ phân biệt đều thỏa mãn bất đẳng thức tam giác. Với dãy có ít hơn ba phần tử, điều kiện này luôn đúng.

Xét tất cả các dãy TriSeq có đúng $N$ phần tử, mỗi phần tử thuộc $[1,N]$. Sắp xếp chúng theo thứ tự từ điển và đánh số bắt đầu từ $1$: tại vị trí khác nhau đầu tiên, dãy có phần tử nhỏ hơn đứng trước.

Hãy thực hiện ba yêu cầu: đếm tổng số dãy; tìm dãy có thứ tự $T$; tìm thứ tự của dãy $A$ được cho.

### Dữ liệu vào

- Dòng đầu chứa số nguyên dương $N$.
- Dòng thứ hai chứa số nguyên dương $T$.
- Dòng thứ ba chứa $N$ số nguyên $A_1,\ldots,A_N$.

### Dữ liệu ra

- Dòng đầu in tổng số dãy TriSeq thỏa mãn.
- Dòng thứ hai in $N$ phần tử của dãy có thứ tự $T$.
- Dòng thứ ba in thứ tự của dãy $A$.

### Ràng buộc

- $1\le N\le18$.
- $1\le A_i\le N$; $A$ là một dãy TriSeq.
- $1\le T\le$ tổng số dãy TriSeq có độ dài $N$ với giá trị trong $[1,N]$.
- Các kết quả cần in chính xác, không lấy modulo.

### Sample Input 1

```text
3
4
2 1 2
```

### Sample Output 1

```text
15
2 1 2
4
```

### Giải thích

Với $N=3$, có $15$ dãy, theo thứ tự:

$(1,1,1)$, $(1,2,2)$, $(1,3,3)$, $(2,1,2)$, $(2,2,1)$, $(2,2,2)$, $(2,2,3)$, $(2,3,2)$, $(2,3,3)$, $(3,1,3)$, $(3,2,2)$, $(3,2,3)$, $(3,3,1)$, $(3,3,2)$, $(3,3,3)$.

Vì vậy dãy thứ $4$ là $(2,1,2)$, và thứ tự của dãy đầu vào cũng là $4$.
