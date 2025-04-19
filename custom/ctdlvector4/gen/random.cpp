#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int T_MAX = 10000;
const int LIMIT = 1000;
const int A_MAX = 1e9;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, T_MAX);
    cout << t << '\n';
    auto n = gen.gen_sum<int>(LIMIT, t, 0, LIMIT);
    auto m = gen.gen_sum<int>(LIMIT, t, 0, LIMIT);

    for (int i = 0; i < t; ++i) {
        cout << n[i] + 1 << ' ' << m[i] + 1 << '\n';
        for (int a = 0; a <= n[i]; a++)
            for (int b = 0; b <= m[i]; b++)
                cout << gen.uniform(1, A_MAX) << " \n"[b == m[i]];
    }
    return 0;
}
