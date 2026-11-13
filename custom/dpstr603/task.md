# DPSTR603 — Giữ lại thông điệp đối xứng

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Bạn được xóa một số ký tự để các ký tự còn lại tạo thành một xâu đối xứng. Hãy tìm số ký tự lớn nhất có thể giữ lại. Không được đổi thứ tự hoặc thay đổi các ký tự được giữ.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

Một **dãy con** được tạo bằng cách xóa một số vị trí, có thể không xóa vị trí nào, và giữ nguyên thứ tự các ký tự còn lại. Các vị trí giữ lại không bắt buộc liên tiếp; mỗi vị trí chỉ được dùng một lần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số ký tự lớn nhất có thể giữ lại để tạo xâu đối xứng.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
4
abca
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
6
abcdef
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, có thể giữ `aba` hoặc `aca`, đều dài $3$; toàn xâu không đối xứng. Ở ví dụ 2, các chữ đều khác nhau nên chỉ giữ được một ký tự.
