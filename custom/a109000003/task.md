# A109000003 — Tổng tiền hàng

### Đề bài

Một tệp nhị phân lưu $N$ dòng hàng. Mỗi dòng có mã hàng, số lượng và đơn giá. Thành tiền của một dòng bằng số lượng nhân đơn giá. Hãy tính tổng thành tiền của tất cả các dòng; những dòng trùng mã vẫn được tính riêng.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000003.INP`**.
- Đầu tệp là số nguyên $N$ kiểu `int`, cho biết số bản ghi.
- Tiếp theo là đúng $N$ bản ghi `MatHang`, mỗi bản ghi gồm `id`, `quantity` (số lượng), `price` (đơn giá).
- Cấu trúc `MatHang` được khai báo như sau:

```cpp
struct MatHang {
    int id;
    int quantity;
    long long price;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000003.OUT`**.

In một số nguyên là tổng thành tiền.

### Ràng buộc

- $1\le N\le200000$; $1\le\text{id}\le10^9$.
- $0\le\text{quantity}\le10000$; $0\le\text{price}\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
02 00 00 00 01 00 00 00 03 00 00 00 10 27 00 00
00 00 00 00 02 00 00 00 02 00 00 00 a8 61 00 00
00 00 00 00
```

### Sample Output 1

```text
80000
```

### Sample Input 2

```text
02 00 00 00 09 00 00 00 00 00 00 00 58 1b 00 00
00 00 00 00 08 00 00 00 04 00 00 00 00 00 00 00
00 00 00 00
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Hai dòng hàng là `(1, 3, 10000)` và `(2, 2, 25000)`. Tổng là $3\cdot10000+2\cdot25000=80000$.

**Ví dụ 2:** Hai dòng hàng là `(9, 0, 7000)` và `(8, 4, 0)`, đều có thành tiền bằng $0$.
