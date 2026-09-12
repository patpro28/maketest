#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(10000, 1e5);
    int q = gen.uniform<int>(10000, 1e5);
    auto edges = gen.tree<int>(n, true);
    cout << n << " " << q << "\n";
    for (auto e : edges) {
        cout << e.first << " " << e.second << "\n";
    }
    while (q--) {
        int a = 0, b = 0, c = gen.uniform<int>(1, n);
        while (a == b) {
            a = gen.uniform<int>(1, n);
            b = gen.uniform<int>(1, n);
        }
        cout << a << " " << b << " " << c << "\n";
    }
    return 0;
}
