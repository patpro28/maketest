# SEGTREE216 — Nhiệt độ trung bình

### Đề bài

Có $N$ trạm với số đo nhiệt độ nguyên $A_i$ tại trạm $i$. Bạn cần tính nhiệt độ trung bình **chính xác** của các trạm trong đoạn được hỏi.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào số đo của từng trạm trong đoạn $[L,R]$.
- `2 L R`. In hai số nguyên $p,q$ biểu diễn nhiệt độ trung bình dưới dạng phân số tối giản $p/q$, với $q>0$ và $\gcd(|p|,q)=1$. Nếu trung bình bằng $0$, in `0 1`.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác. Hai số trên cùng một dòng cách nhau bởi một dấu cách.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10^8$ ở đầu vào.

### Sample Input 1

```text
4 5
1 2 -2 1
2 1 4
1 2 4 -2
2 1 4
2 2 4
2 3 3
```

### Sample Output 1

```text
1 2
-1 1
-5 3
-4 1
```

### Sample Input 2

```text
2 3
-3 3
2 1 2
1 1 2 1
2 1 2
```

### Sample Output 2

```text
0 1
1 1
```

### Giải thích

Ở ví dụ 1, trung bình ban đầu là $2/4=1/2$. Sau cập nhật, dãy là $[1,0,-4,-1]$. Ba kết quả tiếp theo là $-4/4$, $-5/3$ và $-4/1$.

Ở ví dụ 2, hai số đo ban đầu có tổng $0$. Sau cập nhật, chúng là $-2$ và $4$, có trung bình $1$.
