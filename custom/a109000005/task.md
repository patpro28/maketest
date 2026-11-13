# A109000005 — Số dư cuối ngày

### Đề bài

Một tài khoản có số dư ban đầu $B$ và $N$ giao dịch được lưu trong tệp nhị phân. Giao dịch loại $1$ cộng tiền vào tài khoản, loại $2$ trừ tiền khỏi tài khoản. Hãy tính số dư sau tất cả giao dịch. Số dư được phép âm; không bỏ qua giao dịch nào.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000005.INP`**.
- Đầu tệp là một `Header` gồm `n` ($N$), `initial` ($B$).
- Tiếp theo là đúng $N$ bản ghi `GiaoDich`, mỗi bản ghi gồm `type` (loại giao dịch), `amount` (số tiền).
- Các cấu trúc dữ liệu được khai báo như sau:

```cpp
struct Header {
    int n;
    long long initial;
};

struct GiaoDich {
    unsigned char type;
    long long amount;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000005.OUT`**.

In một số nguyên là số dư cuối cùng.

### Ràng buộc

- $1\le N\le200000$; $-10^{12}\le B\le10^{12}$.
- $\text{type}\in\{1,2\}$; $0\le\text{amount}\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
03 00 00 00 00 00 00 00 64 00 00 00 00 00 00 00
01 00 00 00 00 00 00 00 32 00 00 00 00 00 00 00
02 00 00 00 00 00 00 00 1e 00 00 00 00 00 00 00
02 00 00 00 00 00 00 00 14 00 00 00 00 00 00 00
```

### Sample Output 1

```text
100
```

### Sample Input 2

```text
02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
02 00 00 00 00 00 00 00 0a 00 00 00 00 00 00 00
01 00 00 00 00 00 00 00 04 00 00 00 00 00 00 00
```

### Sample Output 2

```text
-6
```

### Giải thích

**Ví dụ 1:** Số dư ban đầu là $100$. Ba giao dịch lần lượt là `(1, 50)`, `(2, 30)`, `(2, 20)`, nên số dư cuối là $100+50-30-20=100$.

**Ví dụ 2:** Số dư ban đầu là $0$. Trừ $10$ rồi cộng $4$ được $-6$.
