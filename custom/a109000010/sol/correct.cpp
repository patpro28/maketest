#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header {
    char magic[4];
    unsigned int n;
};

struct Ngay {
    unsigned short year;
    unsigned char month;
    unsigned char day;
};

struct NhietDo {
    Ngay date;
    int temperature;
};
static_assert(sizeof(NhietDo) == 8, "NhietDo size");
static_assert(sizeof(Header) == 8, "Header size");
static_assert(sizeof(Ngay) == 4, "Ngay size");

int main() {
    ifstream fin("A109000010.INP", ios::binary);
    ofstream fout("A109000010.OUT");
    if (!fin || !fout) return 1;
    Header h; if (!fin.read(reinterpret_cast<char*>(&h), sizeof(h))) return 0;
    NhietDo best; fin.read(reinterpret_cast<char*>(&best), sizeof(best));
    for (unsigned int i = 1; i < h.n; ++i) {
        NhietDo r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.temperature > best.temperature) best = r;
    }
    fout << unsigned(best.date.day) << ' ' << unsigned(best.date.month) << ' '
         << best.date.year << ' ' << best.temperature << '\n';
}
