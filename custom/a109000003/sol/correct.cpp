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
