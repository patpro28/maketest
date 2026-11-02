# SEGTREE204 — Rút gọn các con số

### Đề bài

Cho dãy số nguyên dương $A_1,A_2,\dots,A_N$. Thực hiện lần lượt $Q$ thao tác:

- `1 L R x`: với mỗi $i\in[L,R]$, thay $A_i$ bằng $\gcd(A_i,x)$.
- `2 p`: cho biết giá trị hiện tại của $A_p$.

Ở đây $\gcd(u,v)$ là ước chung lớn nhất của hai số nguyên dương $u,v$. Mỗi cập nhật sử dụng giá trị hiện tại của phần tử, không phải giá trị ban đầu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: giá trị hiện tại của phần tử được hỏi. Thao tác loại `1` không yêu cầu in kết quả.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i\le1000000000$ ở thời điểm ban đầu.
- Với thao tác loại `1`: $1\le L\le R\le N$.
- Với thao tác loại `1`: $1\le x\le10^9$.
- Với thao tác loại `2`: $1\le p\le N$.

### Sample Input 1

```text
4 6
12 18 30 7
1 1 3 6
2 2
1 2 4 4
2 1
2 3
2 4
```

### Sample Output 1

```text
6
6
2
1
```

### Sample Input 2

```text
3 5
24 35 49
1 1 3 14
1 2 3 21
2 1
1 1 3 1
2 3
```

### Sample Output 2

```text
2
1
```

### Giải thích

Ở ví dụ 1, cập nhật đầu tạo dãy $[6,6,6,7]$, nên câu trả lời đầu là $6$. Cập nhật tiếp theo tạo dãy $[6,2,2,1]$; ba câu trả lời cuối là $6,2,1$.

Ở ví dụ 2, hai cập nhật đầu tạo dãy $[2,7,7]$. Sau khi lấy GCD với $1$ trên toàn dãy, mọi phần tử đều bằng $1$.
