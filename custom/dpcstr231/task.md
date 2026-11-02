# DPCSTR231 — Bản sao có lỗi

### Đề bài

Cho hai xâu chữ thường $A,B$ và số nguyên $K$. Chọn hai đoạn con liên tiếp có cùng độ dài $L$, mỗi đoạn trong một xâu. Đặt hai đoạn cạnh nhau và so sánh các ký tự ở cùng độ lệch từ đầu đoạn. Hai đoạn được chấp nhận nếu có không quá $K$ cặp ký tự khác nhau.

Hãy tìm độ dài $L$ lớn nhất. Được phép chọn hai đoạn rỗng với $L=0$.

Một **đoạn con liên tiếp** của xâu là các ký tự ở một dãy vị trí liên tiếp, giữ nguyên thứ tự. Vị trí trong mỗi xâu được đánh số từ $1$. Không được bỏ qua ký tự nằm giữa hai đầu của một đoạn.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,K$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài lớn nhất của hai đoạn có không quá $K$ cặp ký tự khác nhau.

### Ràng buộc

- $1\le N,M\le2500$.
- Các xâu đầu vào chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le K\le5$.

### Sample Input 1

```text
4 4 1
abcd
abxd
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
3 3 0
aaa
bbb
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, giữ cả hai xâu: chỉ cặp ký tự thứ ba khác nhau, nằm trong giới hạn một lỗi. Ở ví dụ 2, không được có lỗi trong khi không có ký tự chung, nên đáp án là $0$.
