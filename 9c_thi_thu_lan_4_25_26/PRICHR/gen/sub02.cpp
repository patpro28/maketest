#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
#define endl '\n'
using namespace std;

const long long MAX_L = 1e3;
const long long MAX_R = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 1000);
    cout << t << endl;
    auto N = gen.gen_sum<int>(2e5, t, 2, 1e5);

    while (t--) {
        int n = N.back();
        N.pop_back();
        cout << n << '\n';
        string s = gen.lower_string(n);
        cout << s << '\n';
        int k = gen.uniform(1, 26);
        cout << k << ' ';
        auto perm = gen.perm<int>(26);
        for (int i = 0; i < k; ++i)
            cout << char('a' + perm[i]) << ' ';
        cout << endl;
    }
    return 0;
}
