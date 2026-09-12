#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(2, 100);
    auto N = gen.gen_sum<int>(1e6, t, 1);
    cout << t << "\n";
    for (int i = 0; i < t - 1; i++) {
        int n = N[i];
        cout << n << '\n';
        string a(n, '0');
        for (int j = 0; j < n; ++j) {
            a[j] = gen.uniform_bool() ? '1' : '0';
        }
        cout << a << '\n';
        int k = gen.uniform(1, 10);
        if (k == 1) {
            for (int j = 0; j < n; ++j) {
                a[j] = gen.uniform_bool() ? '1' : '0';
            }
            cout << a << '\n';
            continue;
        }
        int l = gen.uniform(0, n - 1);
        int r = gen.uniform(l, n - 1);
        for (int j = l; j <= r; ++j) {
            a[j] = '1' + '0' - a[j];
        }
        l = gen.uniform(0, n - 1);
        r = gen.uniform(l, n - 1);
        for (int j = l; j <= r; ++j) {
            a[j] = '1' + '0' - a[j];
        }
        cout << a << '\n';
    }
    // last test case
    int n = N[t - 1];
    cout << n << '\n';
    string a(n, '0');
    for (int j = 0; j < n; ++j) {
        a[j] = gen.uniform_bool() ? '1' : '0';
    }
    cout << a << '\n';
    cout << a << '\n';
    return 0;
}
