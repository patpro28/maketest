## Ý tưởng

Đọc `Header` để lấy $N,T$. Đọc đúng $N$ bản ghi; tăng bộ đếm khi `score >= threshold`.

## Tính đúng đắn

Sau mỗi bản ghi, bộ đếm bằng số học sinh đạt yêu cầu trong phần đã đọc, vì chỉ tăng khi và chỉ khi điểm đủ ngưỡng. Sau $N$ bản ghi, bộ đếm chính là kết quả cần tìm.

## Độ phức tạp

Thời gian $O(N)$, bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Dùng nguyên khai báo `struct` trong đề với cách bố trí mặc định của C++. Đọc toàn bộ `sizeof` của bản ghi, bao gồm các byte đệm mà trình biên dịch thêm vào. Chương trình dưới đây dành cho máy little-endian và dùng cách bố trí struct mặc định. Dùng `ifstream fin("A109000002.INP", ios::binary)` để mở tệp đầu vào và `ofstream fout("A109000002.OUT")` để mở tệp kết quả dạng văn bản. Dùng `fin.read` để lấy cả bản ghi, không dùng `>>`. Chế độ `ios::binary` giữ nguyên các byte đầu vào trên cả Windows.

## C++11

```cpp
#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header {
    int n;
    int threshold;
};

struct HocSinh {
    int id;
    int score;
};
static_assert(sizeof(HocSinh) == 8, "HocSinh size");
static_assert(sizeof(Header) == 8, "Header size");

int main() {
    ifstream fin("A109000002.INP", ios::binary);
    ofstream fout("A109000002.OUT");
    if (!fin || !fout) return 1;
    Header h; if (!fin.read(reinterpret_cast<char*>(&h), sizeof(h))) return 0;
    int answer = 0;
    for (int i = 0; i < h.n; ++i) {
        HocSinh r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.score >= h.threshold) ++answer;
    }
    fout << answer << '\n';
}
```
