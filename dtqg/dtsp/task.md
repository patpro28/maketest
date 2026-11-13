# DTSP — Bán hàng khuyến mại

### Đề bài

Mỗi nắp hộp sữa loại $1$, loại $2$, loại $3$ lần lượt có giá trị $1$, $2$, $3$ điểm. Có thể đổi một nhóm nắp lấy một chú gấu bông nếu tổng điểm của nhóm **ít nhất bằng $s$**.

Mẹ Bông có $a$ nắp loại $1$, $b$ nắp loại $2$ và $c$ nắp loại $3$. Mỗi nắp chỉ được dùng trong nhiều nhất một lần đổi. Điểm vượt mức của một nhóm không được chuyển sang lần đổi khác; có thể không dùng hết các nắp.

Hãy tìm số gấu bông lớn nhất có thể nhận được.

### Dữ liệu vào

Đọc từ tệp `SP.INP`:

- Dòng duy nhất chứa bốn số nguyên $a,b,c,s$.

### Dữ liệu ra

Ghi ra tệp `SP.OUT` một số nguyên là số gấu bông lớn nhất có thể nhận được.

### Ràng buộc

- $0\le a,b,c\le270$.
- $1\le s\le10^6$.

### Sample Input 1

```text
1 2 1 4
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
0 0 4 4
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, chia thành hai nhóm điểm $1+3$ và $2+2$, mỗi nhóm đổi được một chú gấu.

Ở ví dụ 2, mỗi nhóm cần ít nhất hai nắp loại $3$. Bốn nắp chỉ đổi được hai chú gấu, dù tổng điểm bằng $12$.

### Nguồn

Chuyển từ `sp.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
