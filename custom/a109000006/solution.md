## Ý tưởng

Khởi tạo ba tổng 64 bit bằng $0$. Với mỗi bản ghi, cộng số lượng vào tổng có chỉ số `kind - 1`.

## Tính đúng đắn

Mỗi bản ghi được cộng đúng một lần vào đúng loại của nó. Vì không có phép cộng nào sang loại khác, sau khi đọc hết, ba tổng lần lượt là tổng số lượng của ba loại.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Đọc số lượng bản ghi trực tiếp vào biến `int n` bằng `fin.read(reinterpret_cast<char*>(&n), sizeof(n))`, rồi đọc lần lượt $N$ bản ghi.

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000006.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000006.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Dùng `long long` cho tổng để tránh tràn số nguyên 32 bit. Các giới hạn bảo đảm kết quả nằm trong miền số nguyên có dấu 64 bit.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct SanPham {
    unsigned char kind;
    int quantity;
};
static_assert(sizeof(SanPham) == 8, "SanPham size");

int main() {
    ifstream fin("A109000006.INP", ios::binary);
    ofstream fout("A109000006.OUT");
    if (!fin || !fout) return 1;
    int n;
    if (!fin.read(reinterpret_cast<char*>(&n), sizeof(n))) return 0;
    long long total[3] = {0, 0, 0};
    for (int i = 0; i < n; ++i) {
        SanPham r; fin.read(reinterpret_cast<char*>(&r), sizeof(r)); total[r.kind - 1] += r.quantity;
    }
    fout << total[0] << ' ' << total[1] << ' ' << total[2] << '\n';
}
```
