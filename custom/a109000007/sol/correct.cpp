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
