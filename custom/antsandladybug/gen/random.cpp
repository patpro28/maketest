#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 5000);
    int k = gen.uniform(1, n);
    vector<int> a = gen.choice(k, 1, n);
    cout << n << '\n';
    auto edges = gen.tree<int>(n, 1);
    for (auto [u, v]: edges) {
        cout << u << ' ' << v << '\n';
    }
    cout << k << '\n';
    for (int i = 0; i < k; ++i) {
        cout << a[i] << " \n"[i == k - 1];
    }
    int l = 500;
    cout << l << '\n';
    for (int i = 0; i < l; ++i) {
        cout << gen.uniform(1, n) << ' ';
    }
    return 0;
}
