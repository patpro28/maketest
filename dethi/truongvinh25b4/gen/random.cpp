#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500000);
    int q = gen.uniform(1, 100000);
    vector<int> value;
    int m = gen.uniform(1, n);
    map<int, int> used;
    for (int i = 0; i < m; ++i) {
        int v = gen.uniform<int>(1, 1e9);
        while (used.count(v)) {
            v = gen.uniform<int>(1, 1e9);
        }
        used[v] = 1;
        value.push_back(v);
    }
    cout << n << ' ' << q << "\n";
    for (int i = 0; i < n; ++i) {
        cout << value[gen.uniform(0, m - 1)] << ' ';
    }
    cout << "\n";
    int k = gen.uniform(1, m);
    for (int i = 0; i < k; ++i) {
        int v = gen.uniform<int>(1, 1e9);
        while (used.count(v)) {
            v = gen.uniform<int>(1, 1e9);
        }
        used[v] = 1;
        value.push_back(v);
    }
    while (q--) {
        cout << value[gen.uniform(0, (int)value.size() - 1)] << "\n";
    }
    return 0;
}
