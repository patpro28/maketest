# A109000001 — Tổng giá trị trong tệp

### Đề bài

Một tệp nhị phân lưu các bản ghi gồm mã và giá trị của các món đồ. Hãy tính tổng giá trị của mọi bản ghi. Mã chỉ dùng để nhận diện, không tham gia phép tính; các mã có thể trùng nhau. Tệp có thể rỗng, khi đó tổng bằng $0$.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000001.INP`**.
- Tệp không có phần đầu và không chứa số lượng bản ghi.
- Từ byte đầu đến cuối tệp là các `DoVat` liên tiếp; mỗi bản ghi gồm `id`, `value`. Đọc cho đến khi hết tệp.
- Cấu trúc `DoVat` được khai báo như sau:

```cpp
struct DoVat {
    int id;
    int value;
};
```

**Hướng dẫn vào/ra tệp nhị phân**

Dùng thư viện `<fstream>`. Mở tệp đầu vào với `ios::binary` và mở tệp đầu ra ở chế độ văn bản:

```cpp
using namespace std;
ifstream fin("A109000001.INP", ios::binary);
ofstream fout("A109000001.OUT");
```

Đọc mỗi bản ghi bằng `read`, dùng kết quả của lần đọc làm điều kiện lặp:

```cpp
DoVat r;
while (fin.read((char*)&r, sizeof(r))) {
    // Xử lý dữ liệu trong r.id và r.value.
}
```

Ghi kết quả bằng `fout << ketQua;`. Không dùng toán tử `>>` để đọc các trường nhị phân. Nếu đầu tệp chứa một số nguyên riêng, có thể đọc trực tiếp bằng `fin.read((char*)&n, sizeof(n))`, không cần tạo struct chỉ để chứa số đó.

Trong nhóm bài A109, máy chấm dùng thứ tự byte little-endian, byte $8$ bit; `int` và `unsigned int` chiếm $4$ byte, `long long` chiếm $8$ byte, `unsigned short` chiếm $2$ byte, `char` và `unsigned char` chiếm $1$ byte. Các struct dùng cách bố trí mặc định của C++, gồm cả byte đệm do trình biên dịch thêm; đọc và ghi theo `sizeof`.

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000001.OUT`**.

In một số nguyên là tổng giá trị.

### Ràng buộc

- $0\le N\le200000$, trong đó $N$ là số bản ghi suy ra từ độ dài tệp.
- $1\le\text{id}\le10^9$; $-10^9\le\text{value}\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
01 00 00 00 07 00 00 00 02 00 00 00 fd ff ff ff
03 00 00 00 05 00 00 00
```

### Sample Output 1

```text
9
```

### Sample Input 2

```text
0a 00 00 00 fc ff ff ff 0b 00 00 00 fa ff ff ff
```

### Sample Output 2

```text
-10
```

### Giải thích

**Ví dụ 1:** Các cặp `(id, value)` là `(1, 7)`, `(2, -3)`, `(3, 5)`. Tổng là $7-3+5=9$.

**Ví dụ 2:** Hai giá trị là $-4$ và $-6$, tổng bằng $-10$.
