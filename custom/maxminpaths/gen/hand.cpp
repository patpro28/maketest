#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1;
    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
        int n = 200000;
        int m = 100;
        cout << n << ' ' << 300 << '\n';
        auto edges = gen.tree<int>(300 - m, true); // 289 canh
        // 10 -> 299
        for (auto [u, v]: edges) {
            cout << u + m - 1 << ' ' << v + m - 1 << '\n'; 
        }
        // -> 10 -> 300 -> 302
        cout << 300 << ' ' << 301 << '\n';  // 1 canh
        cout << 301 << ' ' << m << '\n';   // 1 canh
        cout << 301 << ' ' << 302 << '\n';  // 1 canh
        for (int i = 1; i < m - 1; ++i)
            cout << i << ' ' << i + 1 << '\n';  // 8 canh
        cout << m - 1 << ' ' << 200000 << '\n';         // 1 canh
        cout << 200000 << ' ' << m << '\n';        // 1 canh
        edges = gen.tree<int>(200000 - 301 - 1, true); // 199697 canh
        // 302 -> 199999
        for (auto [u, v]: edges) {
            cout << u + 301 << ' ' << v + 301 << '\n';
        }
        // So canh = 289 + 1 + 1 + 1 + 8 + 1 + 199697 = 200000
    }

    return 0;
}
