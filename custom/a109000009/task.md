# A109000009 — Sách còn trong kho

### Đề bài

Một tệp nhị phân lưu mã sách và số cuốn còn trong kho của $N$ bản ghi. Hãy in những bản ghi có số cuốn lớn hơn $0$, theo đúng thứ tự trong tệp. Không gộp các bản ghi trùng mã.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000009.INP`**.
- Đầu tệp là số nguyên $N$ kiểu `int`, cho biết số bản ghi.
- Tiếp theo là đúng $N$ bản ghi `Sach`, mỗi bản ghi gồm `code` (mã sách, đệm bằng `0` nếu chưa đủ $12$ ký tự), `stock` (số cuốn).
- Cấu trúc `Sach` được khai báo như sau:

```cpp
struct Sach {
    char code[12];
    int stock;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000009.OUT`**.

Dòng đầu in số bản ghi có `stock` lớn hơn $0$. Sau đó, với mỗi bản ghi được chọn, in một dòng gồm mã sách và số cuốn, cách nhau một dấu cách. Giữ nguyên thứ tự xuất hiện; không in các byte `0` đệm sau mã. Nếu không có bản ghi nào được chọn, chỉ in dòng `0`.

### Ràng buộc

- $1\le N\le200000$.
- Mã gồm từ $1$ đến $12$ chữ cái ASCII in hoa `A`–`Z`.
- $0\le\text{stock}\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
03 00 00 00 54 4f 41 4e 00 00 00 00 00 00 00 00
04 00 00 00 56 41 4e 00 00 00 00 00 00 00 00 00
00 00 00 00 54 49 4e 00 00 00 00 00 00 00 00 00
02 00 00 00
```

### Sample Output 1

```text
2
TOAN 4
TIN 2
```

### Sample Input 2

```text
01 00 00 00 41 42 43 44 45 46 47 48 49 4a 4b 4c
00 00 00 00
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Ba bản ghi là `(TOAN, 4)`, `(VAN, 0)`, `(TIN, 2)`. In hai bản ghi `TOAN` và `TIN` theo thứ tự ban đầu.

**Ví dụ 2:** Mã `ABCDEFGHIJKL` chiếm đủ $12$ byte, có số cuốn bằng $0$ nên không được in.
