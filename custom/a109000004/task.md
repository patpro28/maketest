# A109000004 — Học sinh có tổng điểm cao nhất

### Đề bài

Một tệp nhị phân lưu mã học sinh và điểm của ba môn. Hãy tìm học sinh có tổng điểm ba môn lớn nhất. Nếu có nhiều học sinh cùng tổng điểm lớn nhất, chọn bản ghi xuất hiện trước trong tệp.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000004.INP`**.
- Đầu tệp là số nguyên $N$ kiểu `int`, cho biết số bản ghi.
- Tiếp theo là đúng $N$ bản ghi `HocSinh`, mỗi bản ghi gồm `code` (mã) và mảng `score` chứa đúng ba điểm theo thứ tự môn 1, môn 2, môn 3.
- Cấu trúc `HocSinh` được khai báo như sau:

```cpp
struct HocSinh {
    char code[8];
    int score[3];
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000004.OUT`**.

In trên một dòng mã học sinh được chọn và tổng điểm ba môn, cách nhau một dấu cách. Không in các byte `0` đệm sau mã.

### Ràng buộc

- $1\le N\le200000$.
- Mã gồm từ $1$ đến $8$ chữ cái ASCII in hoa `A`–`Z`.
- $0\le\text{score}[j]\le10$ với $0\le j<3$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
03 00 00 00 41 4e 00 00 00 00 00 00 08 00 00 00
07 00 00 00 09 00 00 00 42 49 4e 48 00 00 00 00
09 00 00 00 09 00 00 00 09 00 00 00 43 48 49 00
00 00 00 00 0a 00 00 00 08 00 00 00 09 00 00 00
```

### Sample Output 1

```text
BINH 27
```

### Sample Input 2

```text
01 00 00 00 41 42 43 44 45 46 47 48 00 00 00 00
00 00 00 00 00 00 00 00
```

### Sample Output 2

```text
ABCDEFGH 0
```

### Giải thích

**Ví dụ 1:** Các bản ghi là `AN: 8 7 9`, `BINH: 9 9 9`, `CHI: 10 8 9`. `BINH` và `CHI` cùng có tổng $27$; chọn `BINH` vì xuất hiện trước.

**Ví dụ 2:** Mã `ABCDEFGH` chiếm đủ $8$ byte và không có byte kết thúc. Tổng ba điểm là $0$.
