#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header {
    int n;
    long long initial;
};

struct GiaoDich {
    unsigned char type;
    long long amount;
};
static_assert(sizeof(GiaoDich) == 16, "GiaoDich size");
static_assert(sizeof(Header) == 16, "Header size");

int main() {
    ifstream fin("A109000005.INP", ios::binary);
    ofstream fout("A109000005.OUT");
    if (!fin || !fout) return 1;
    Header h; if (!fin.read(reinterpret_cast<char*>(&h), sizeof(h))) return 0;
    long long balance = h.initial;
    for (int i = 0; i < h.n; ++i) {
        GiaoDich r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (r.type == 1) balance += r.amount;
        else balance -= r.amount;
    }
    fout << balance << '\n';
}
