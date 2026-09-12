#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(10, 200);
    int m = gen.uniform<int>(10, 200);
    int d = gen.uniform<int>(1, 1000);
    cout << n << " " << m << " " << d << "\n";
    vector<vector<int>> a(n, vector<int>(m));
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = d * gen.uniform<int>(0, 10000 / d);
            mx = max(mx, a[i][j]);
        }
    }
    a[n - 1][m - 1] += 1; // make no solution
    int v = gen.uniform<int>(0, 1e4 - mx);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] += v;
            cout << a[i][j] << (j == m - 1 ? "\n" : " ");
        }
    }
    return 0;
}
