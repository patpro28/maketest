# A109000002 — Đếm học sinh đạt yêu cầu

### Đề bài

Một tệp nhị phân lưu điểm của $N$ học sinh và điểm yêu cầu $T$. Một học sinh đạt yêu cầu nếu điểm của em đó lớn hơn hoặc bằng $T$. Hãy đếm số học sinh đạt yêu cầu. Mỗi bản ghi được tính là một học sinh, kể cả khi mã trùng nhau.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000002.INP`**.
- Đầu tệp là một `Header` gồm `n` ($N$) và `threshold` ($T$).
- Tiếp theo là đúng $N$ bản ghi `HocSinh`, mỗi bản ghi gồm `id`, `score`.
- Các cấu trúc dữ liệu được khai báo như sau:

```cpp
struct Header {
    int n;
    int threshold;
};

struct HocSinh {
    int id;
    int score;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000002.OUT`**.

In một số nguyên là số học sinh đạt yêu cầu.

### Ràng buộc

- $1\le N\le200000$; $0\le T\le10$.
- $1\le\text{id}\le10^9$; $0\le\text{score}\le10$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
04 00 00 00 05 00 00 00 01 00 00 00 08 00 00 00
02 00 00 00 04 00 00 00 03 00 00 00 05 00 00 00
04 00 00 00 00 00 00 00
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
02 00 00 00 0a 00 00 00 07 00 00 00 03 00 00 00
08 00 00 00 09 00 00 00
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** $N=4$, $T=5$, các điểm lần lượt là $8,4,5,0$. Có hai điểm lớn hơn hoặc bằng $5$.

**Ví dụ 2:** $T=10$, hai điểm là $3,9$, không học sinh nào đạt yêu cầu.
