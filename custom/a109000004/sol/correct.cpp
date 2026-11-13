#include <fstream>
using namespace std;

static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct HocSinh {
    char code[8];
    int score[3];
};
static_assert(sizeof(HocSinh) == 20, "HocSinh size");

int main() {
    ifstream fin("A109000004.INP", ios::binary);
    ofstream fout("A109000004.OUT");
    if (!fin || !fout) return 1;
    int n;
    if (!fin.read(reinterpret_cast<char*>(&n), sizeof(n))) return 0;
    HocSinh best; fin.read(reinterpret_cast<char*>(&best), sizeof(best));
    int bestSum = best.score[0] + best.score[1] + best.score[2];
    for (int i = 1; i < n; ++i) {
        HocSinh r; fin.read(reinterpret_cast<char*>(&r), sizeof(r));
        int sum = r.score[0] + r.score[1] + r.score[2];
        if (sum > bestSum) { best = r; bestSum = sum; }
    }
    int length = 0;
    while (length < 8 && best.code[length] != '\0') ++length;
    fout.write(best.code, length);
    fout << ' ' << bestSum << '\n';
}
