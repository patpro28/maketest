## Ý tưởng

Đọc số nguyên $N$ ở đầu tệp. Với mỗi dòng hàng, nhân số lượng với đơn giá bằng số nguyên 64 bit rồi cộng vào tổng 64 bit.

## Tính đúng đắn

Mỗi dòng đóng góp chính xác số lượng nhân đơn giá vào tổng. Vòng lặp xét tất cả các dòng một lần và không loại bỏ dòng trùng mã, do đó tổng thu được đúng theo yêu cầu.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Đọc số lượng bản ghi trực tiếp vào biến `int n` bằng `fin.read(reinterpret_cast<char*>(&n), sizeof(n))`, rồi đọc lần lượt $N$ bản ghi.

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000003.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000003.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Dùng `long long` cho tổng để tránh tràn số nguyên 32 bit. Các giới hạn bảo đảm kết quả nằm trong miền số nguyên có dấu 64 bit.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct MatHang {
    int id;
    int quantity;
    long long price;
};
static_assert(sizeof(MatHang) == 16, "MatHang size");

int main() {
    ifstream fin("A109000003.INP", ios::binary);
    ofstream fout("A109000003.OUT");
    if (!fin || !fout) return 1;
    int n;
    if (!fin.read(reinterpret_cast<char*>(&n), sizeof(n))) return 0;
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        MatHang r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        total += static_cast<long long>(r.quantity) * r.price;
    }
    fout << total << '\n';
}
```
