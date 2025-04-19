#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int q = 100000;
    cout << n << '\n';
    vector<int> v(3);
    for (int i = 0; i < 3; i++) {
        v[i] = gen.uniform<int>(-1000000000, 1000000000);
    }
    vector<int> a(n);
    for (auto &x: a) x = v[gen.uniform<int>(0, 2)];
    sort(a.begin(), a.end());
    for (auto x: a) cout << x << ' ';
    cout << '\n';
    cout << q << '\n';
    while (q--) {
        cout << v[gen.uniform<int>(0, 2)] << '\n';
    }

    return 0;
}
