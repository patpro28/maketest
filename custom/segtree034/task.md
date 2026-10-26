# SEGTREE034 — Chênh lệch với mốc

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r c`: tính ước chung lớn nhất (GCD) của các độ chênh lệch tuyệt đối $|A_l-c|,|A_{l+1}-c|,\ldots,|A_r-c|$.

Mốc $c$ có thể khác nhau ở mỗi truy vấn. Quy ước GCD của toàn các số $0$ bằng $0$; các số $0$ còn lại không làm thay đổi GCD, chẳng hạn $\gcd(0,6)=6$. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r c`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa GCD của các độ chênh lệch tuyệt đối so với mốc được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x,c\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
4 6
6 10 14 22
2 1 4 2
2 2 3 6
1 3 13
2 1 4 2
2 3 3 13
2 3 4 4
```

### Sample Output 1

```text
4
4
1
0
9
```

### Sample Input 2

```text
2 4
-1000000000 -1000000000
2 1 2 1000000000
2 1 2 -1000000000
1 2 1000000000
2 1 2 0
```

### Sample Output 2

```text
2000000000
0
1000000000
```

### Giải thích

Ở ví dụ 1, với mốc $2$, cả dãy có các chênh lệch $4,8,12,20$, GCD bằng $4$. Đoạn $[2,3]$ so với mốc $6$ có các chênh lệch $4,8$, cũng cho GCD bằng $4$. Sau khi gán $A_3=13$, truy vấn toàn dãy so với mốc $2$ có các chênh lệch $4,8,11,20$, GCD bằng $1$. Phần tử $A_3$ bằng mốc $13$ nên truy vấn một phần tử cho $0$. Truy vấn cuối lấy GCD của $9,18$, bằng $9$.

Ở ví dụ 2, hai chênh lệch ban đầu so với mốc $10^9$ đều bằng $2\cdot10^9$. Khi mốc bằng các phần tử thì tất cả chênh lệch bằng $0$. Sau khi sửa phần tử thứ hai, hai chênh lệch so với mốc $0$ đều bằng $10^9$.
