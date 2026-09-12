#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100);
    auto N = gen.gen_sum<int>(2e5, t);
    auto M = gen.gen_sum<int>(2e5, t);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int n = N[i], m = M[i];
        cout << n << ' ' << m << '\n';
        int mi = 1e9;
        vector<int> a(n), b(m);
        for (auto &x : a) {
            x = gen.uniform<int>(1, 1e9);
            mi = min(mi, x);
        }
        int k = gen.uniform(1, 10);
        if (k == 1) {
            for (auto &x : b) {
                x = gen.uniform<int>(1, 1e9);
            }
        } else {
            for (auto &x : b) {
                x = gen.uniform<int>(mi, 1e9);
            }
        }
        for (auto x : a) {
            cout << x << " ";
        } 
        cout << "\n";
        for (auto x : b) {
            cout << x << " ";
        } 
        cout << "\n";
    }
    return 0;
}
