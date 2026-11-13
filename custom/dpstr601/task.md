# DPSTR601 — Đoạn gương dài nhất

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Hãy tìm độ dài lớn nhất của một đoạn **liên tiếp** đối xứng trong $S$, đồng thời tìm vị trí bắt đầu của đoạn đó. Nếu có nhiều đoạn dài nhất, chọn đoạn có vị trí bắt đầu nhỏ nhất. Các vị trí được đánh số từ $1$.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In hai số nguyên $len,pos$: độ dài đoạn đối xứng dài nhất và vị trí bắt đầu nhỏ nhất của một đoạn đạt độ dài đó.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
5
babad
```

### Sample Output 1

```text
3 1
```

### Sample Input 2

```text
4
cbbd
```

### Sample Output 2

```text
2 2
```

### Giải thích

Ở ví dụ 1, `bab` tại vị trí $1$ và `aba` tại vị trí $2$ đều dài $3$; chọn vị trí $1$ theo quy tắc ưu tiên. Ở ví dụ 2, đoạn dài nhất là `bb`, bắt đầu ở vị trí $2$.
