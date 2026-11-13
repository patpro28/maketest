## Ý tưởng

Đọc bản ghi đầu tiên làm kết quả tạm thời. Với mỗi bản ghi còn lại, tính tổng ba điểm. Chỉ thay kết quả khi tổng mới lớn hơn tổng đang giữ.

## Tính đúng đắn

Sau mỗi bước, kết quả tạm thời có tổng điểm lớn nhất trong phần đã đọc. Khi tổng bằng nhau, không thay kết quả, nên luôn giữ bản ghi xuất hiện trước. Tính chất này đúng từ bản ghi đầu tiên và được duy trì đến hết tệp.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Đọc số lượng bản ghi trực tiếp vào biến `int n` bằng `fin.read(reinterpret_cast<char*>(&n), sizeof(n))`, rồi đọc lần lượt $N$ bản ghi.

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000004.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000004.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

Mã có thể chiếm đủ mảng và không có byte `0` kết thúc. Xác định độ dài trong giới hạn kích thước mảng, rồi in lần lượt các ký tự trong giới hạn đó; không truyền trực tiếp mảng chưa chắc kết thúc vào hàm xử lý chuỗi C.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct HocSinh {
    char code[8];
    int score[3];
};
static_assert(sizeof(HocSinh) == 20, "HocSinh size");

int main() {
    ifstream fin("A109000004.INP", ios::binary);
    ofstream fout("A109000004.OUT");
    if (!fin || !fout) return 1;
    int n;
    if (!fin.read(reinterpret_cast<char*>(&n), sizeof(n))) return 0;
    HocSinh best; fin.read(reinterpret_cast<char*>(&best), sizeof(best));
    int bestSum = best.score[0] + best.score[1] + best.score[2];
    for (int i = 1; i < n; ++i) {
        HocSinh r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        int sum = r.score[0] + r.score[1] + r.score[2];
        if (sum > bestSum) { best = r; bestSum = sum; }
    }
    int length = 0;
    while (length < 8 && best.code[length] != '\0') ++length;
    fout.write(best.code, length);
    fout << ' ' << bestSum << '\n';
}
```
