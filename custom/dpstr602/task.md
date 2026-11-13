# DPSTR602 — Đếm đoạn gương

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Hãy đếm số cặp chỉ số $(L,R)$ thỏa $1\le L\le R\le N$ và đoạn **liên tiếp** $S[L\ldots R]$ đối xứng. Hai đoạn có vị trí khác nhau được tính riêng, kể cả khi nội dung giống nhau. Không tính đoạn rỗng.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số đoạn đối xứng không rỗng. Kết quả được in chính xác, không lấy modulo.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3
aaa
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
4
abca
```

### Sample Output 2

```text
4
```

### Giải thích

Ở ví dụ 1, có ba đoạn dài $1$, hai đoạn dài $2$ và một đoạn dài $3$, tổng cộng $6$. Ở ví dụ 2, chỉ bốn đoạn một ký tự đối xứng; `aba` và `aca` có thể là dãy con nhưng không phải đoạn liên tiếp của `abca`.
