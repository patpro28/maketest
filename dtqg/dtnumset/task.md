# DTNUMSET — Tập số

### Đề bài

Cho số nguyên không âm $n$ được viết trong hệ thập phân, không có chữ số `0` vô nghĩa ở đầu.

Chọn một hoặc nhiều chữ số của $n$, giữ nguyên thứ tự và xóa các chữ số còn lại. Chuẩn hóa kết quả bằng cách bỏ các chữ số `0` vô nghĩa ở đầu; nếu tất cả chữ số được giữ đều là `0` thì kết quả là số $0$.

Gọi $D$ là tập các giá trị số khác nhau có thể nhận được. Được phép giữ nguyên mọi chữ số, nên $n$ cũng thuộc $D$. Các cách chọn khác nhau nhưng cho cùng giá trị chỉ đóng góp một phần tử.

Ví dụ, với $n=101$, ta có $D=\{0,1,10,11,101\}$.

Cho hai số nguyên không âm $A\le B$. Hãy đếm số phần tử của $D$ nằm trong đoạn $[A,B]$. Kết quả cần in chính xác, không lấy modulo.

### Dữ liệu vào

Đọc từ tệp `NUMSET.INP`:

- Dòng thứ nhất chứa số $n$.
- Dòng thứ hai chứa số $A$.
- Dòng thứ ba chứa số $B$.

### Dữ liệu ra

Ghi ra tệp `NUMSET.OUT` một số nguyên là số giá trị cần đếm.

### Ràng buộc

- $n,A,B$ không có chữ số `0` vô nghĩa ở đầu; số $0$ được viết là `0`.
- $0\le A\le B$.
- Dữ liệu thuộc ít nhất một trong hai dạng sau:
  - Mỗi số $n,A,B$ có không quá $1000$ chữ số.
  - Mỗi số $n,A,B$ có không quá $200000$ chữ số và $B-A\le1000000$.

### Sample Input 1

```text
101
1
100
```

### Sample Output 1

```text
3
```

### Giải thích

Trong ví dụ 1, ba giá trị thuộc $D\cap[1,100]$ là $1,10,11$.

### Nguồn

Chuyển từ `NUMSET.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
