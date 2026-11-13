#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct DoVat {
    int id;
    int value;
};
static_assert(sizeof(DoVat) == 8, "DoVat size");

int main() {
    ifstream fin("A109000001.INP", ios::binary);
    ofstream fout("A109000001.OUT");
    if (!fin || !fout) return 1;
    DoVat r; long long total = 0;
    while (fin.read(reinterpret_cast<char*>(&r), sizeof(r))) total += r.value;
    fout << total << '\n';
}
