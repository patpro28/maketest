# A109000008 — Tổng thời gian hoạt động

### Đề bài

Một tệp nhị phân lưu các khoảng thời gian của một máy. Trạng thái `R` nghĩa là máy đang chạy, `S` nghĩa là máy đang dừng. Mỗi bản ghi cho biết trạng thái và số giây của khoảng đó. Hãy tính tổng số giây máy chạy. Tệp có thể rỗng, khi đó kết quả bằng $0$.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000008.INP`**.
- Tệp không có phần đầu và không chứa số lượng bản ghi.
- Từ byte đầu đến cuối tệp là các `HoatDong` liên tiếp; mỗi bản ghi gồm `state` (trạng thái), `seconds` (số giây). Đọc cho đến khi hết tệp.
- Cấu trúc `HoatDong` được khai báo như sau:

```cpp
struct HoatDong {
    char state;
    int seconds;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000008.OUT`**.

In một số nguyên là tổng số giây máy chạy.

### Ràng buộc

- $0\le N\le200000$, trong đó $N$ là số bản ghi suy ra từ độ dài tệp.
- $\text{state}\in\{\texttt{R},\texttt{S}\}$; $0\le\text{seconds}\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
52 00 00 00 05 00 00 00 53 00 00 00 03 00 00 00
52 00 00 00 07 00 00 00
```

### Sample Output 1

```text
12
```

### Sample Input 2

```text
53 00 00 00 08 00 00 00 53 00 00 00 00 00 00 00
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Các bản ghi là `(R, 5)`, `(S, 3)`, `(R, 7)`. Hai khoảng chạy có tổng $5+7=12$ giây.

**Ví dụ 2:** Các bản ghi là `(S, 8)`, `(S, 0)`, không có khoảng chạy nên kết quả bằng $0$.
