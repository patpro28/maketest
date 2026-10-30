#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "fast_io.h"
using namespace std;
using ll = long long;

int main() {
    FastInput in;
    FastOutput out;
    int n, m, q; in >> n >> m >> q;
    vector<vector<ll>> p(n + 1, vector<ll>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ll x; in >> x;
            p[i][j] = x + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
        }
    }
    while (q--) {
        int x1, y1, x2, y2; in >> x1 >> y1 >> x2 >> y2;
        out << p[x2][y2] - p[x1 - 1][y2] - p[x2][y1 - 1] + p[x1 - 1][y1 - 1] << '\n';
    }
}
