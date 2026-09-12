#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAXQ = 100000;
const int MINN = 10000;
const int MAXN = 50000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int m = gen.uniform(MINN, MAXN);
    auto n1 = gen.gen_sum<int>(m, 26, 0);
    auto n2 = gen.gen_sum<int>(m, 26, 0);
    string s = "";
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < n1[i]; ++j) s += (char)('a' + i);
        for (int j = 0; j < n2[i]; ++j) s += (char)('A' + i);
    }
    gen.shuffle(s.begin(), s.end());
    cout << s << "\n";
    int q = gen.uniform(1, MAXQ);
    cout << q << "\n";
    for (int i = 0; i < q; ++i) {
        int x = gen.uniform(1, m * 2);
        int y = gen.uniform(1, m * 2);
        cout << x << " " << y << "\n";
    }
    return 0;
}
