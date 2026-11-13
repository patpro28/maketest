# DPSTR200 — Đoạn tin trùng nhau

### Đề bài

Cho hai xâu chữ thường $A,B$, có độ dài lần lượt là $N,M$. Hãy tìm độ dài lớn nhất của một đoạn con liên tiếp xuất hiện trong cả hai xâu. Nếu không có ký tự chung, đáp án là $0$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài đoạn con liên tiếp chung dài nhất.

### Ràng buộc

- $1\le N,M\le5000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 5
abcde
abzde
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 3
aaa
bbb
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, `ab` và `de` đều là đoạn chung dài $2$. Dãy `abde` không liên tiếp nên không được chọn. Ở ví dụ 2, hai xâu không có ký tự chung.
