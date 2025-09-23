#include <iostream>
#include <vector>
#include <map>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, 10000);
    auto K = gen.gen_sum(100000, t);
    auto Q = gen.gen_sum(100000, t);
    cout << t << endl;
    while (t--) {
        int n = gen.uniform<int>(K[t], 1e9);
        cout << n << ' ' << K[t] << ' ' << Q[t] << '\n';
        vector<int> a(K[t]);
        map<int, bool> used;
        for (int i = 1; i < K[t]; ++i) {
            a[i] = gen.uniform<int>(1, n - 1);
            while (used[a[i]]) {
                a[i] = gen.uniform<int>(1, n - 1);
            }
            used[a[i]] = true;
        }
        sort(a.begin(), a.end());
        for (int i = 1; i < K[t]; ++i) {
            cout << a[i] << ' ';
        }
        cout << n << '\n';
        for (int i = 0; i < K[t]; ++i) {
            a[i] = gen.uniform<int>(1, 1e9);
            while (used[a[i]]) {
                a[i] = gen.uniform<int>(1, 1e9);
            }
            used[a[i]] = true;
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < K[t]; ++i)
            cout << a[i] << ' ';
        cout << '\n';
        while (Q[t]--) {
            cout << gen.uniform<int>(0, n) << '\n';
        }
    }
    return 0;
}
