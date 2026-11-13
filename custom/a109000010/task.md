# A109000010 — Ngày có nhiệt độ cao nhất

### Đề bài

Một tệp nhị phân lưu $N$ bản ghi nhiệt độ. Mỗi bản ghi chứa ngày đo và nhiệt độ nguyên. Hãy tìm bản ghi có nhiệt độ cao nhất và in ngày đo cùng nhiệt độ đó. Nếu có nhiều bản ghi cùng nhiệt độ cao nhất, chọn bản ghi xuất hiện trước trong tệp; không cần so sánh ngày tháng.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000010.INP`**.
- Đầu tệp là một `Header`: `magic` là đúng bốn byte ASCII `A109` (không có byte kết thúc), sau đó `n` là số bản ghi $N$.
- Tiếp theo là đúng $N$ bản ghi `NhietDo`: `date` là một `Ngay` gồm `year`, `month`, `day`; sau đó là `temperature` (nhiệt độ).
- Các cấu trúc dữ liệu được khai báo như sau:

```cpp
struct Header {
    char magic[4];
    unsigned int n;
};

struct Ngay {
    unsigned short year;
    unsigned char month;
    unsigned char day;
};

struct NhietDo {
    Ngay date;
    int temperature;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000010.OUT`**.

In trên một dòng bốn số nguyên theo thứ tự ngày, tháng, năm, nhiệt độ của bản ghi được chọn, cách nhau một dấu cách. Ngày và tháng không cần thêm chữ số `0` ở đầu.

### Ràng buộc

- $1\le N\le200000$.
- $2000\le\text{year}\le2100$; $1\le\text{month}\le12$; $1\le\text{day}\le28$.
- $-100\le\text{temperature}\le100$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
41 31 30 39 03 00 00 00 ea 07 01 02 19 00 00 00
ea 07 01 03 1c 00 00 00 ea 07 01 04 1c 00 00 00
```

### Sample Output 1

```text
3 1 2026 28
```

### Sample Input 2

```text
41 31 30 39 02 00 00 00 e9 07 0c 01 fb ff ff ff
e9 07 0c 02 f8 ff ff ff
```

### Sample Output 2

```text
1 12 2025 -5
```

### Giải thích

**Ví dụ 1:** Sau phần đầu `A109`, $N=3$. Ba lần đo lần lượt là ngày 2/1/2026: $25$, ngày 3/1/2026: $28$, ngày 4/1/2026: $28$. Chọn ngày 3/1/2026 vì xuất hiện trước trong hai bản ghi cao nhất.

**Ví dụ 2:** Hai lần đo là ngày 1/12/2025: $-5$ và ngày 2/12/2025: $-8$. Nhiệt độ cao nhất là $-5$.
