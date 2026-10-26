# SEGTREE081 — Mức tăng tốt nhất

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: chọn hai vị trí $i,j$ sao cho $l\le i<j\le r$ và $A_j-A_i$ lớn nhất, rồi in giá trị lớn nhất đó.

Mọi đoạn truy vấn có ít nhất hai phần tử. Bạn bắt buộc chọn hai vị trí khác nhau, với $i$ đứng trước $j$; không được đổi thứ tự hai vị trí. Vì vậy đáp án có thể âm. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa giá trị lớn nhất của $A_j-A_i$ với $l\le i<j\le r$. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $2\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l<r\le N$.

### Sample Input 1

```text
6 6
8 3 6 1 5 4
2 1 6
2 1 3
2 4 6
1 2 10
2 1 3
2 2 3
```

### Sample Output 1

```text
4
3
4
2
-4
```

### Sample Input 2

```text
4 4
9 7 5 3
2 1 4
2 1 2
1 4 12
2 1 4
```

### Sample Output 2

```text
-2
-2
7
```

### Giải thích

Ở ví dụ 1, truy vấn toàn dãy đầu tiên chọn $i=4,j=5$, được $5-1=4$. Truy vấn $[1,3]$ chọn $i=2,j=3$, được $6-3=3$. Đoạn $[4,6]$ cũng có đáp án $4$. Sau khi gán $A_2=10$, đoạn $[1,3]$ có đáp án $10-8=2$, còn đoạn $[2,3]$ chỉ có thể chọn hiệu $6-10=-4$.

Ở ví dụ 2, dãy ban đầu giảm nghiêm ngặt nên mọi lựa chọn đều cho hiệu âm; đáp án lớn nhất là $-2$. Sau khi sửa phần tử cuối thành $12$, chọn hai giá trị $5,12$ theo đúng thứ tự để được hiệu $7$.
