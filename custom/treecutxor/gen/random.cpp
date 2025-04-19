#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1e9;
const int MIN = 10;
const int T_MAX = 10000;
const int N_MAX = 200000;


int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, T_MAX);

    cout << t << endl;
    int limit = N_MAX / t;
    while (t--) {
        int n = gen.uniform<int>(1, limit);
        auto edges = gen.tree<int>(n, true);
        cout << n << endl;
        for (auto [u, v] : edges) {
            cout << u << " " << v << endl;
        }
    }

    return 0;
}
