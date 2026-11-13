## Ý tưởng

Đọc số dư ban đầu vào biến 64 bit. Với mỗi giao dịch, cộng `amount` nếu `type == 1`, ngược lại trừ `amount`.

## Tính đúng đắn

Ban đầu biến số dư đúng bằng số dư trước giao dịch. Mỗi bước thực hiện đúng phép cộng hoặc trừ của giao dịch tương ứng. Bởi vậy sau giao dịch cuối cùng, biến lưu chính xác số dư cần in.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000005.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000005.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Dùng `long long` cho tổng để tránh tràn số nguyên 32 bit. Các giới hạn bảo đảm kết quả nằm trong miền số nguyên có dấu 64 bit.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header {
    int n;
    long long initial;
};

struct GiaoDich {
    unsigned char type;
    long long amount;
};
static_assert(sizeof(GiaoDich) == 16, "GiaoDich size");
static_assert(sizeof(Header) == 16, "Header size");

int main() {
    ifstream fin("A109000005.INP", ios::binary);
    ofstream fout("A109000005.OUT");
    if (!fin || !fout) return 1;
    Header h; if (!fin.read(reinterpret_cast<char*>(&h), sizeof(h))) return 0;
    long long balance = h.initial;
    for (int i = 0; i < h.n; ++i) {
        GiaoDich r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.type == 1) balance += r.amount;
        else balance -= r.amount;
    }
    fout << balance << '\n';
}
```
