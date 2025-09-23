#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 8);
    string p(n, '0');
    p[0] = gen.uniform(1, 9) + '0';
    for (int i = 1; i < n; ++i)
        p[i] = gen.uniform(0, 9) + '0';
    set<int> S({1, 2, 3, 4, 5, 6, 7, 8, 9});
    int k = gen.uniform(0, 9);
    while (k-- > 0 or (int) S.size() > n) {
        int x = gen.uniform(1, 9);
        S.erase(x);
    }
    cout << p << endl;
    for (int x : S) cout << x;
    return 0;
}
