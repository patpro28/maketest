#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    vector<int> a(n);
    for(auto &x: a) x = gen.uniform<int>(1, 1e6);
    vector<int> b(a);
    for(int i = 1; i < n; i++) {
        b[i] = min(b[i], b[i - 1]);
    }
    cout << n << "\n";
    for(auto x: a) cout << x << " ";
    cout << "\n";
    int q = gen.uniform(1, 200000);
    cout << q << "\n";
    while(q--) {
        int l = gen.uniform(1, n);
        int r = gen.uniform(l, n);
        int x = b[gen.uniform(0, n - 1)];
        cout << l << " " << r << " " << x << "\n";
    }

    return 0;
}
