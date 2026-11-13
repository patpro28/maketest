# DTDNA — So sánh hai đoạn DNA

### Đề bài

Hai đoạn DNA có cùng độ dài và chỉ gồm các ký tự `A`, `D`, `G`, `T`.

Một lần đột biến chọn một đoạn ký tự ở các vị trí liên tiếp rồi đảo ngược thứ tự ký tự trong đoạn đó. Cụ thể, nếu $\alpha=xyz$ thì có thể biến thành $\beta=xy^Rz$, trong đó $y^R$ là xâu $y$ viết ngược; các xâu $x,y,z$ có thể rỗng.

Hai đoạn DNA được gọi là gần giống nhau nếu có thể biến đoạn thứ nhất thành đoạn thứ hai sau **không quá bốn lần** đột biến. Không yêu cầu các đoạn được đảo ở những lần khác nhau phải rời nhau.

Hãy xác định hai đoạn DNA đã cho có gần giống nhau hay không.

### Dữ liệu vào

Đọc từ tệp `DNA.INP`:

- Dòng thứ nhất chứa đoạn DNA thứ nhất.
- Dòng thứ hai chứa đoạn DNA thứ hai.

### Dữ liệu ra

Ghi ra tệp `DNA.OUT` chính xác `Similar` nếu hai đoạn gần giống nhau, ngược lại in `Different`.

### Ràng buộc

- Hai xâu có cùng độ dài $1\le n\le45$.
- Mỗi ký tự thuộc tập `A`, `D`, `G`, `T`.

### Sample Input 1

```text
ATGAATGAATGA
TTTAAAAAAGGG
```

### Sample Output 1

```text
Different
```

### Giải thích

Trong ví dụ 1, không thể biến xâu thứ nhất thành xâu thứ hai bằng không quá bốn lần đảo đoạn, nên kết quả là `Different`.

### Nguồn

Chuyển từ `dna.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
