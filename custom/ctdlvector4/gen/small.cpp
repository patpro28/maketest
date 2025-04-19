#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int T_MAX = 5;
const int LIMIT = 1000;
const int A_MAX = 1e9;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 1);
    cout << t << '\n';
    auto n = gen.gen_sum<int>(LIMIT, t, LIMIT, LIMIT);
    auto m = gen.gen_sum<int>(LIMIT, t, LIMIT, LIMIT);

    for (int i = 0; i < t; ++i) {
        cout << n[i] << ' ' << m[i] << '\n';
        for (int a = 0; a < n[i]; a++)
            for (int b = 0; b < m[i]; b++)
                cout << gen.uniform(1, A_MAX) << " \n"[b == m[i] - 1];
    }
    return 0;
}
