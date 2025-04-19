#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2, 10);
    cout << n << '\n';
    auto edges = gen.tree<int>(n, true);
    for (auto [u, v]: edges) {
        cout << u << ' ' << v << ' ' << gen.uniform(1, 10) << '\n';
    }
    return 0;
}
