#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 1000, m = 1000;
    int q = 1e6;
    cout << n << " " << m << " " << q << endl;
    auto perms = gen.perm<int>(2 * q);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << perms[i * m + j] << ' ';
        cout << endl;
    }
    while (q--) {
        cout << gen.uniform(1, 2 * MAX) << '\n';
    }
    return 0;
}
