## Ý tưởng

Khởi tạo tổng bằng $0$. Đọc lần lượt từng `DoVat` đến hết tệp và cộng `value` vào tổng.

## Tính đúng đắn

Sau khi đọc $k$ bản ghi, biến tổng bằng tổng giá trị của đúng $k$ bản ghi đó. Mỗi lần đọc thêm một bản ghi, phép cộng duy trì tính chất này. Khi hết tệp, mọi bản ghi đã được tính đúng một lần.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000001.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000001.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Dùng kết quả trả về của `read` làm điều kiện vòng lặp. Không dùng `while (!fin.eof())`, vì cờ kết thúc chỉ được đặt sau một lần đọc thất bại.

Dùng `long long` cho tổng để tránh tràn số nguyên 32 bit. Các giới hạn bảo đảm kết quả nằm trong miền số nguyên có dấu 64 bit.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct DoVat {
    int id;
    int value;
};
static_assert(sizeof(DoVat) == 8, "DoVat size");

int main() {
    ifstream fin("A109000001.INP", ios::binary);
    ofstream fout("A109000001.OUT");
    if (!fin || !fout) return 1;
    DoVat r; long long total = 0;
    while (fin.read(reinterpret_cast<char*>(&r), sizeof(r))) total += r.value;
    fout << total << '\n';
}
```
