# DTREBUSS — Điền chữ số trong phép cộng

### Đề bài

Một phép cộng đúng của hai số nguyên dương bị mất một số chữ số; mỗi chữ số bị mất được thay bằng ký tự `*`.

Cho ba xâu lần lượt biểu diễn hai số hạng và tổng. **Dấu `*` có thể xuất hiện trong cả hai số hạng và tổng.** Hãy thay mỗi dấu `*` bằng một chữ số từ `0` đến `9` sao cho phép cộng đúng. Các dấu `*` được chọn độc lập, không bắt buộc thay bằng cùng một chữ số.

Không được thay đổi các chữ số đã biết, thứ tự chữ số hoặc độ dài của bất kỳ xâu nào. Chữ số đầu tiên của mỗi số phải khác `0`, kể cả số chỉ có một chữ số. Nếu có nhiều lời giải, in một lời giải bất kỳ.

### Dữ liệu vào

Đọc từ tệp `REBUSS.INP`:

- Dòng thứ nhất chứa xâu biểu diễn số hạng thứ nhất.
- Dòng thứ hai chứa xâu biểu diễn số hạng thứ hai.
- Dòng thứ ba chứa xâu biểu diễn tổng.

### Dữ liệu ra

Ghi ra tệp `REBUSS.OUT`:

- Nếu có lời giải, in ba dòng là ba số sau khi thay các dấu `*`, theo đúng thứ tự đầu vào.
- Nếu không có lời giải, in chính xác `No Solution`.

### Ràng buộc

- Mỗi xâu có độ dài từ $1$ đến $100000$.
- Mỗi ký tự là một chữ số từ `0` đến `9` hoặc dấu `*`.
- Dữ liệu không bảo đảm có lời giải. Một xâu bắt đầu bằng chữ số `0` đã biết cũng không thể được chấp nhận.

### Sample Input 1

```text
*3*4
78*
10123
```

### Sample Output 1

```text
9334
789
10123
```

### Giải thích

Ở ví dụ 1, thay ba dấu `*` tương ứng bằng $9,3,9$ để nhận được $9334+789=10123$.

### Nguồn

Chuyển từ `Rebuss.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
