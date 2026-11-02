# DPCSTR250 — Ba bản ghi

### Đề bài

Cho ba xâu chữ thường $A,B,D$, có độ dài lần lượt là $N,M,P$. Tìm độ dài lớn nhất của một đoạn con liên tiếp xuất hiện trong cả ba xâu. Nếu không có ký tự chung của cả ba xâu, đáp án là $0$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,P$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa xâu $D$ có đúng $P$ ký tự.

### Dữ liệu ra

In độ dài đoạn con liên tiếp chung dài nhất của ba xâu.

### Ràng buộc

- $1\le N,M,P\le350$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
6 5 5
abcdef
zbcdy
xbcda
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
1 1 1
a
b
a
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, `bcd` xuất hiện trong cả ba xâu, có độ dài $3$, và không có đoạn chung dài hơn. Ở ví dụ 2, chữ `a` không xuất hiện trong xâu thứ hai nên không có ký tự chung của cả ba.
