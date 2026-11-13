# DPSTR651 — Đối xứng với ít lần thay chữ

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường và số nguyên $K$. Bạn chọn một dãy con của $S$, sau đó được thay **không quá $K$ ký tự trong dãy đã chọn**, mỗi lần thay một ký tự bằng một chữ cái thường khác, để dãy đó trở thành xâu đối xứng.

Hãy tìm độ dài lớn nhất của dãy con có thể chọn. Các lần thay không làm thay đổi độ dài. Không tính thêm số cách chọn hoặc số cách thay chữ.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

Một **dãy con** được tạo bằng cách xóa một số vị trí, có thể không xóa vị trí nào, và giữ nguyên thứ tự các ký tự còn lại. Các vị trí giữ lại không bắt buộc liên tiếp; mỗi vị trí chỉ được dùng một lần.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In độ dài lớn nhất của dãy con có thể biến thành xâu đối xứng với không quá $K$ lần thay ký tự.

### Ràng buộc

- $1\le N\le4000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le K\le5$.

### Sample Input 1

```text
4 1
abcd
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4 0
abca
```

### Sample Output 2

```text
3
```

### Giải thích

Ở ví dụ 1, chọn `abc` rồi thay `c` bằng `a` để được `aba`, dài $3$. Giữ cả bốn chữ sẽ cần sửa cả hai cặp đầu–cuối, vượt $K=1$. Ở ví dụ 2, không được thay chữ, nhưng có thể chọn `aba` hoặc `aca` dài $3$.
