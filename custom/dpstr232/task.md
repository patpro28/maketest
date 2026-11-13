# DPSTR232 — Đếm đoạn tin chung

### Đề bài

Cho hai xâu chữ thường $A,B$, có độ dài lần lượt là $N,M$. Hãy đếm số bộ ba $(l_A,l_B,L)$ thỏa mãn:

- $L\ge1$; hai đoạn bắt đầu tại $l_A,l_B$ và có độ dài $L$ đều nằm trọn trong xâu tương ứng.
- $A_{l_A+t}=B_{l_B+t}$ với mọi $0\le t<L$.

Các bộ có vị trí bắt đầu hoặc độ dài khác nhau được tính riêng, kể cả khi nội dung các đoạn giống nhau. In kết quả chính xác, không lấy modulo.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số bộ ba thỏa mãn yêu cầu.

### Ràng buộc

- $1\le N,M\le5000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 2
aaa
aa
```

### Sample Output 1

```text
8
```

### Sample Input 2

```text
2 2
ab
ba
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, độ dài $1$ có $3\cdot2=6$ bộ; độ dài $2$ có $2\cdot1=2$ bộ, tổng cộng $8$. Ở ví dụ 2, chỉ có hai đoạn một ký tự `a` và `b` được ghép theo vị trí tương ứng.
