#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100);
    auto N = gen.gen_sum<int>(1e3, t);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int n = N[i];
        cout << n << "\n";
        vector<int> w(n);
        vector<int> a(n);
        for (auto &x : a) {
            x = gen.uniform<int>(2, 1e2);
        }
        for (int i = 0; i < n; ++i) {
            w[i] = gen.uniform<int>(1, a[i] - 1);
        }
        for (auto x : w) {
            cout << x << " ";
        } 
        cout << "\n";
        for (auto x : a) {
            cout << x << " ";
        } 
        cout << "\n";
    }
        
    return 0;
}
