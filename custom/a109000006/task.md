# A109000006 — Thống kê ba loại sản phẩm

### Đề bài

Các sản phẩm thuộc một trong ba loại $1$, $2$, $3$. Một tệp nhị phân lưu $N$ bản ghi, mỗi bản ghi cho biết loại sản phẩm và số lượng. Hãy tính tổng số lượng của từng loại. Loại không xuất hiện có tổng bằng $0$.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000006.INP`**.
- Đầu tệp là số nguyên $N$ kiểu `int`, cho biết số bản ghi.
- Tiếp theo là đúng $N$ bản ghi `SanPham`, mỗi bản ghi gồm `kind` (loại), `quantity` (số lượng).
- Cấu trúc `SanPham` được khai báo như sau:

```cpp
struct SanPham {
    unsigned char kind;
    int quantity;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000006.OUT`**.

In trên một dòng ba số nguyên lần lượt là tổng số lượng của loại $1$, $2$, $3$, cách nhau một dấu cách.

### Ràng buộc

- $1\le N\le200000$.
- $\text{kind}\in\{1,2,3\}$; $0\le\text{quantity}\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
04 00 00 00 01 00 00 00 05 00 00 00 03 00 00 00
02 00 00 00 01 00 00 00 04 00 00 00 02 00 00 00
00 00 00 00
```

### Sample Output 1

```text
9 0 2
```

### Sample Input 2

```text
01 00 00 00 02 00 00 00 07 00 00 00
```

### Sample Output 2

```text
0 7 0
```

### Giải thích

**Ví dụ 1:** Các bản ghi `(kind, quantity)` là `(1, 5)`, `(3, 2)`, `(1, 4)`, `(2, 0)`. Tổng ba loại lần lượt là $9,0,2$.

**Ví dụ 2:** Chỉ có bản ghi `(2, 7)`, nên hai loại còn lại có tổng $0$.
