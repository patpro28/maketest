#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10);
    auto N = gen.gen_sum(2000, t, 2);
    cout << t << endl;
    for (int i = 0; i < t; ++i) {
        int n = N[i];
        cout << n << endl;
        string s(n, '0');
        for (int j = 0; j < n; ++j) {
            s[j] = gen.uniform(0, 1) + '0';
        }
        cout << s << endl;
        auto par = gen.perm<int>(n - 1);
        for (auto &u: par) cout << u + 1 << ' ';
        cout << endl;
    }
    return 0;
}
