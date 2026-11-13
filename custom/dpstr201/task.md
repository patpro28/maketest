# DPSTR201 — Định vị đoạn tin

### Đề bài

Cho hai xâu chữ thường $A,B$, có độ dài lần lượt là $N,M$. Tìm đoạn con liên tiếp chung dài nhất và vị trí bắt đầu của nó trong mỗi xâu.

Nếu có nhiều phương án cùng độ dài, ưu tiên vị trí bắt đầu trong $A$ nhỏ nhất; nếu vẫn hòa, ưu tiên vị trí bắt đầu trong $B$ nhỏ nhất.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In ba số nguyên $L,l_A,l_B$: độ dài lớn nhất và hai vị trí bắt đầu được chọn. Nếu không có ký tự chung, in `0 0 0`.

### Ràng buộc

- $1\le N,M\le5000$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5 5
ababa
babab
```

### Sample Output 1

```text
4 1 2
```

### Sample Input 2

```text
2 2
aa
bb
```

### Sample Output 2

```text
0 0 0
```

### Giải thích

Ở ví dụ 1, `abab` xuất hiện từ vị trí $1$ trong $A$ và vị trí $2$ trong $B$. Đoạn `baba` cũng dài $4$ nhưng bắt đầu muộn hơn trong $A$. Ở ví dụ 2, không có đoạn chung không rỗng.
