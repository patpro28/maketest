## Ý tưởng

Dùng năm bộ đếm. Nếu một tọa độ bằng $0$, tăng bộ đếm trên trục. Ngược lại, xét dấu của hai tọa độ để tăng đúng bộ đếm góc phần tư.

## Tính đúng đắn

Mỗi điểm hoặc nằm trên trục, hoặc có hai tọa độ khác $0$. Trong trường hợp sau, cặp dấu xác định duy nhất một góc phần tư. Các nhánh loại trừ nhau và phủ hết các trường hợp, nên mỗi điểm được đếm đúng một lần vào đúng nhóm.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Đọc số lượng bản ghi trực tiếp vào biến `int n` bằng `fin.read(reinterpret_cast<char*>(&n), sizeof(n))`, rồi đọc lần lượt $N$ bản ghi.

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000007.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000007.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Diem {
    int x;
    int y;
};
static_assert(sizeof(Diem) == 8, "Diem size");

int main() {
    ifstream fin("A109000007.INP", ios::binary);
    ofstream fout("A109000007.OUT");
    if (!fin || !fout) return 1;
    int n;
    if (!fin.read(reinterpret_cast<char*>(&n), sizeof(n))) return 0;
    int count[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < n; ++i) {
        Diem r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.x == 0 || r.y == 0) ++count[4];
        else if (r.x > 0 && r.y > 0) ++count[0];
        else if (r.x < 0 && r.y > 0) ++count[1];
        else if (r.x < 0 && r.y < 0) ++count[2];
        else ++count[3];
    }
    for (int j = 0; j < 5; ++j) fout << (j ? " " : "") << count[j];
    fout << '\n';
}
```
