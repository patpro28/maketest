# DPSTR130 — Thông điệp có điểm

### Đề bài

Cho hai xâu chữ thường $A,B$ và điểm thưởng $W_c$ của từng chữ cái $c$ từ `a` đến `z`. Điểm của một xâu bằng tổng điểm của tất cả ký tự trong xâu; mỗi lần xuất hiện của một ký tự đều được tính điểm.

Hãy tìm điểm lớn nhất của một dãy con chung của $A$ và $B$. Được phép chọn xâu rỗng với điểm bằng $0$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa $26$ số nguyên $W_a,W_b,\ldots,W_z$, theo thứ tự chữ cái từ `a` đến `z`.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N,M\le 600$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $0\le W_c\le10^9$ với mọi chữ cái $c$.

### Sample Input 1

```text
3 3
abc
cab
1 1 10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
3 2
aaa
aa
7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### Sample Output 2

```text
14
```

### Giải thích

Ở ví dụ 1, chọn `c` được $10$ điểm, tốt hơn dãy chung dài hơn `ab` chỉ có $2$ điểm. Ở ví dụ 2, chọn `aa`; hai lần xuất hiện của `a` đều được tính điểm, tổng cộng $14$.
