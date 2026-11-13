# DPSTR632 — Đếm cách giữ xâu đối xứng

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Hãy đếm số cách chọn một tập vị trí **không rỗng**, đọc các vị trí đã chọn theo thứ tự tăng dần, sao cho xâu nhận được đối xứng. Hai tập vị trí khác nhau được tính là hai cách khác nhau, kể cả khi tạo ra cùng nội dung.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

Một **dãy con** được tạo bằng cách xóa một số vị trí, có thể không xóa vị trí nào, và giữ nguyên thứ tự các ký tự còn lại. Các vị trí giữ lại không bắt buộc liên tiếp; mỗi vị trí chỉ được dùng một lần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số cách chọn vị trí thỏa mãn yêu cầu, lấy modulo $10^9+7$.

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
7
```

### Sample Input 2

```text
3
aba
```

### Sample Output 2

```text
5
```

### Giải thích

Ở ví dụ 1, mọi tập không rỗng trong ba vị trí đều tạo xâu đối xứng, có $2^3-1=7$ cách. Ở ví dụ 2, có ba cách chọn một vị trí, một cách chọn hai chữ `a`, và một cách chọn cả ba vị trí, tổng cộng $5$.
