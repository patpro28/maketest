# DPSTR154 — Hai bản ghi lệch độ dài

### Đề bài

Cho hai xâu chữ thường $A$ và $B$, có độ dài lần lượt là $N$ và $M$. Xâu $A$ có không quá $5000$ ký tự, còn xâu $B$ có thể dài tới $10^6$ ký tự.

Hãy tìm độ dài lớn nhất của một xâu $T$ là dãy con của cả $A$ và $B$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$ và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ **không bắt buộc liên tiếp**. Mỗi vị trí chỉ được sử dụng một lần. Các ký tự giống nhau có thể xuất hiện nhiều lần trong mỗi xâu.

Xâu rỗng là dãy con của mọi xâu và có độ dài $0$. Không có điều kiện bắt buộc $N\le M$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài dãy con chung dài nhất của $A$ và $B$.

### Ràng buộc

- $1\le N\le5000$.
- $1\le M\le10^6$.
- $A,B$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 7
abcde
xaybzcq
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4 6
aaab
cccccc
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
3 2
aaa
ba
```

### Sample Output 3

```text
1
```

### Giải thích

Ở ví dụ 1, có thể giữ `abc` trong cả hai xâu. Các chữ `d`, `e` không xuất hiện trong $B$, nên không thể chọn dài hơn $3$.

Ở ví dụ 2, hai xâu không có ký tự chung, nên chọn xâu rỗng.

Ở ví dụ 3, xâu $B$ chỉ có một chữ `a`. Dù $A$ có ba chữ `a`, mỗi vị trí của $B$ chỉ được dùng một lần nên đáp án là $1$.

### Nguồn

Ý tưởng đảo trạng thái LCS được gợi từ bình luận của RaidenEi trong bài [Swapping DP State Problems trên Codeforces](https://codeforces.com/blog/entry/48874?locale=en). Nội dung đề và các ví dụ ở đây được tự biên soạn.
