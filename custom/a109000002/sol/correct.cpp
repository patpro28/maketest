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
