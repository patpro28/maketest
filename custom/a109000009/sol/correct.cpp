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
