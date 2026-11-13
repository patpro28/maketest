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
