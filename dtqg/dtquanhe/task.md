# DTQUANHE — Quan hệ

### Đề bài

Cho $n$ biến $v_1,v_2,\ldots,v_n$ và $m$ quan hệ giữa các biến. Quan hệ giữa hai chỉ số $i,j$ có một trong các dạng sau.

- `i<j` yêu cầu $v_i<v_j$.
- `i>j` yêu cầu $v_i>v_j$.
- `i<=j` yêu cầu $v_i\le v_j$.
- `i>=j` yêu cầu $v_i\ge v_j$.
- `i=j` yêu cầu $v_i=v_j$.

Hãy gán số nguyên không âm cho các biến sao cho tất cả quan hệ đều thỏa mãn và $\max_{1\le i\le n}v_i$ nhỏ nhất có thể.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,m$.
- Mỗi dòng trong $m$ dòng tiếp theo chứa một quan hệ theo một trong các dạng trên. Dòng biểu diễn quan hệ không chứa dấu cách.

### Dữ liệu ra

In $n$ số nguyên không âm trên một dòng, cách nhau bởi dấu cách, lần lượt là $v_1,v_2,\ldots,v_n$. Nếu có nhiều cách gán đạt giá trị tối ưu, in một cách bất kỳ.

### Ràng buộc

- $1\le n,m\le10^5$.
- $1\le i,j\le n$ trong mọi quan hệ.
- Dữ liệu bảo đảm tồn tại cách gán thỏa mãn tất cả quan hệ.

### Sample Input 1

```text
6 7
1<2
2<3
3=5
6>5
2>=4
4<5
1<=6
```

### Sample Output 1

```text
0 1 2 1 2 3
```

### Giải thích

Trong ví dụ 1, chuỗi quan hệ $v_1<v_2<v_3=v_5<v_6$ buộc $v_6\ge3$. Cách gán trong ví dụ thỏa mãn mọi quan hệ và có giá trị lớn nhất bằng $3$.
