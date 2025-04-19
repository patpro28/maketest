#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    cout << n << '\n';
    for (int i = 0; i < n; ++i)
        cout << gen.uniform(1, n) << ' ';
    cout << '\n';
    auto edges = gen.tree<int>(n, true);
    for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
    
    return 0;
}
