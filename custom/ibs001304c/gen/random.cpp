#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100000);
    cout << n << '\n';
    vector<int> a;
    map<int, bool> used;
    for (int i = 0; i < n + n; ++i) {
        int x = gen.uniform<int>(-1e9, 1e9);
        while (used[x]) {
            x = gen.uniform(-1e9, 1e9);
        }
        used[x] = true;
        a.push_back(x);
    }
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
    int q = gen.uniform(1, 100000);
    cout << q << '\n';
    for (int i = 0; i < q; ++i) {
        cout << a[gen.uniform(0, n + n - 1)] << '\n';
    }
    return 0;
}
