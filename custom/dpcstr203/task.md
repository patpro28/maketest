# DPCSTR203 — Đọc ngược thông điệp

### Đề bài

Cho hai xâu chữ thường $A,B$. Chọn một đoạn con liên tiếp trong mỗi xâu sao cho đoạn của $A$ bằng đoạn của $B$ sau khi đảo ngược thứ tự ký tự. Hãy tìm độ dài lớn nhất có thể chọn. Nếu không có ký tự chung, đáp án là $0$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài lớn nhất của hai đoạn thỏa mãn yêu cầu.

### Ràng buộc

- $1\le N,M\le5000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
4 5
abcd
xdcbz
```

### Sample Output 1

```text
3
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

Ở ví dụ 1, đoạn `bcd` của $A$ bằng đoạn `dcb` của $B$ sau khi đảo ngược, có độ dài $3$. Ở ví dụ 2, không có ký tự chung.
