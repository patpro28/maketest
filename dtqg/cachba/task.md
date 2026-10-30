# CACHBA — Chọn các vị trí cách ba

### Đề bài

Cho dãy $A_1,A_2,\ldots,A_N$, trong đó các giá trị có thể âm. Bạn cần xử lý hai loại thao tác:

- `1 p x`: gán $A_p=x$.
- `2 L R`: chọn một tập vị trí nằm trong đoạn $[L,R]$ sao cho nếu $p<q$ đều được chọn thì $q-p\ge3$. Hãy tìm tổng giá trị lớn nhất tại các vị trí được chọn.

Trong truy vấn loại $2$, được phép không chọn vị trí nào, với tổng bằng $0$. Khoảng cách được tính theo chỉ số trong dãy ban đầu. Các vị trí bên ngoài $[L,R]$ không được chọn và không đặt thêm điều kiện lên truy vấn. Thao tác cập nhật ảnh hưởng tới mọi truy vấn sau đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in tổng lớn nhất trên một dòng, theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le10^5$.
- $-10^9\le A_i,x\le10^9$.
- Với cập nhật: $1\le p\le N$.
- Với truy vấn: $1\le L\le R\le N$.
- Có ít nhất một thao tác loại $2$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
5 5
5 1 9 6 2
2 1 5
2 2 4
1 3 20
2 1 5
2 4 4
```

### Sample Output 1

```text
11
9
20
6
```

### Sample Input 2

```text
1 3
-7
2 1 1
1 1 8
2 1 1
```

### Sample Output 2

```text
0
8
```

### Sample Input 3

```text
4 3
4 4 4 4
2 1 4
1 1 -10
2 1 4
```

### Sample Output 3

```text
8
4
```

### Giải thích

Ở ví dụ 1, truy vấn đầu chọn vị trí $1,4$, tổng bằng $11$. Trong đoạn $[2,4]$, chỉ có thể chọn nhiều nhất một vị trí, nên đáp án là $9$. Sau cập nhật, chọn riêng vị trí $3$ đạt $20$.

Ở ví dụ 2, truy vấn đầu chọn tập rỗng; sau khi giá trị đổi thành $8$, chọn vị trí duy nhất.

Ở ví dụ 3, ban đầu chọn vị trí $1,4$. Sau cập nhật, chọn một trong các vị trí $2,3,4$ đạt tổng lớn nhất bằng $4$.
