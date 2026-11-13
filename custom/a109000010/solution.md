## Ý tưởng

Đọc `Header`, rồi đọc bản ghi đầu tiên làm kết quả. Với mỗi bản ghi còn lại, chỉ thay kết quả khi nhiệt độ mới lớn hơn nhiệt độ đang giữ. In các trường `day`, `month`, `year` của `date` và nhiệt độ.

## Tính đúng đắn

Sau mỗi bước, kết quả có nhiệt độ cao nhất trong phần đã đọc. Chỉ thay khi nhiệt độ lớn hơn nên nếu bằng nhau, bản ghi trước vẫn được giữ. Khi đã đọc đủ $N$ bản ghi, kết quả thỏa cả yêu cầu cực đại lẫn quy tắc hòa.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000010.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000010.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Khi in `day`, `month` là kiểu `unsigned char`, ép sang `unsigned` để in giá trị số thay vì ký tự. `Ngay` được lưu trực tiếp trong `NhietDo`, không dùng con trỏ.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
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
static_assert(sizeof(NhietDo) == 8, "NhietDo size");
static_assert(sizeof(Header) == 8, "Header size");
static_assert(sizeof(Ngay) == 4, "Ngay size");

int main() {
    ifstream fin("A109000010.INP", ios::binary);
    ofstream fout("A109000010.OUT");
    if (!fin || !fout) return 1;
    Header h; if (!fin.read(reinterpret_cast<char*>(&h), sizeof(h))) return 0;
    NhietDo best; fin.read(reinterpret_cast<char*>(&best), sizeof(best));
    for (unsigned int i = 1; i < h.n; ++i) {
        NhietDo r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.temperature > best.temperature) best = r;
    }
    fout << unsigned(best.date.day) << ' ' << unsigned(best.date.month) << ' '
         << best.date.year << ' ' << best.temperature << '\n';
}
```
