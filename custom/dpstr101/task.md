# DPSTR101 — Khôi phục thông điệp

### Đề bài

Cho hai xâu chữ thường $A$ và $B$. Hãy tìm và in ra một dãy con chung dài nhất của hai xâu. Nếu có nhiều đáp án, được phép in bất kỳ đáp án nào.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

Dòng đầu in độ dài $L$ của dãy con chung dài nhất. Nếu $L>0$, dòng thứ hai in một xâu gồm đúng $L$ ký tự là dãy con của cả $A$ và $B$. Nếu $L=0$, chỉ cần in dòng đầu chứa $0$; dòng thứ hai để trống cũng được chấp nhận.

### Ràng buộc

- $1\le N,M\le 1000$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 3
abc
bac
```

### Sample Output 1

```text
2
ac
```

### Sample Input 2

```text
2 2
aa
bb
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, `ac` và `bc` đều là dãy con chung dài nhất, nên cả hai đều được chấp nhận. Đáp án mẫu chọn `ac`. Ở ví dụ 2, không có ký tự chung, nên chỉ cần in $0$.
