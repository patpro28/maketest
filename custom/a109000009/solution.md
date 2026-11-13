## Ý tưởng

Đọc $N$ bản ghi. Đưa những bản ghi có `stock > 0` vào một mảng theo thứ tự đọc. In kích thước mảng, rồi in từng bản ghi trong mảng.

## Tính đúng đắn

Một bản ghi được giữ khi và chỉ khi số cuốn dương, đúng điều kiện yêu cầu. Các bản ghi được thêm và in cùng thứ tự đọc, nên danh sách không đổi thứ tự và không gộp các mã trùng nhau. Kích thước mảng đúng bằng số bản ghi được in.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Đọc số lượng bản ghi trực tiếp vào biến `int n` bằng `fin.read(reinterpret_cast<char*>(&n), sizeof(n))`, rồi đọc lần lượt $N$ bản ghi.

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000009.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000009.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Mã có thể chiếm đủ mảng và không có byte `0` kết thúc. Xác định độ dài trong giới hạn kích thước mảng, rồi in lần lượt các ký tự trong giới hạn đó; không truyền trực tiếp mảng chưa chắc kết thúc vào hàm xử lý chuỗi C.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Sach {
    char code[12];
    int stock;
};
static_assert(sizeof(Sach) == 16, "Sach size");

int main() {
    ifstream fin("A109000009.INP", ios::binary);
    ofstream fout("A109000009.OUT");
    if (!fin || !fout) return 1;
    int n;
    if (!fin.read(reinterpret_cast<char*>(&n), sizeof(n))) return 0;
    Sach kept[200000];
    int count = 0;
    for (int i = 0; i < n; ++i) {
        Sach r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.stock > 0) kept[count++] = r;
    }
    fout << count << '\n';
    for (int i = 0; i < count; ++i) {
        int length = 0;
        while (length < 12 && kept[i].code[length] != '\0') ++length;
        fout.write(kept[i].code, length);
        fout << ' ' << kept[i].stock << '\n';
    }
}
```
