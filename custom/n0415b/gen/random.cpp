#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1e5, 1e6);
    int k = gen.uniform<int>(1, min(n / 2, 1000));
    cout << n << " " << k << "\n";
    int m = n / k;
    set<int> used;
    while ((int) used.size() != m) {
        used.insert(gen.uniform<int>(1, 1e6));
    }
    vector<int> vals(used.begin(), used.end());
    for (int i = 0; i < n; i++) {
        cout << vals[gen.uniform<int>(0, m - 1)] << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
