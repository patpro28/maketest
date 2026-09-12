#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX_M = 2e5;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    auto N = gen.gen_sum<int>(200000, t);
    cout << t << '\n';
    for (auto n : N) {
        int m = gen.uniform<int>(1, min<long long>(1ll * n * (n - 1) / 2, MAX_M));
        map<pair<int, int>, bool> used;
        cout << n << ' ' << m << '\n';
        for (int i = 0; i < m; i++) {
            int a = 1, b = 1;
            while (a == b or used[{a, b}]) {
                a = gen.uniform<int>(1, n);
                b = gen.uniform<int>(1, n);
            }
            used[{a, b}] = used[{b, a}] = true;
            cout << a << ' ' << b << '\n';
        }
        int k = gen.uniform<int>(1, 1e8);
        for (int i = 0; i < n; ++i) {
            cout << gen.uniform<int>(k, k + 100) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
