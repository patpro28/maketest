#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct HoatDong {
    char state;
    int seconds;
};
static_assert(sizeof(HoatDong) == 8, "HoatDong size");

int main() {
    ifstream fin("A109000008.INP", ios::binary);
    ofstream fout("A109000008.OUT");
    if (!fin || !fout) return 1;
    HoatDong r; long long total = 0;
    while (fin.read(reinterpret_cast<char*>(&r), sizeof(r))) if (r.state == 'R') total += r.seconds;
    fout << total << '\n';
}
