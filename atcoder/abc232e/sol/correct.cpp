#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;

using Fp = modint998244353;

int main() {
    int h, w, k;
    cin >> h >> w >> k;
    array<Fp, 2> row = {1, h - 1}, col = {1, w - 1};
    array<array<Fp, 2>, 2> dp = {};
    dp[0][0] = 1;
    while (k--) {
        array<array<Fp, 2>, 2> next = {};
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int a = 0; a < 2; ++a) {
                    next[i][a] += dp[i][j] * (col[a] - (j == a));
                    next[a][j] += dp[i][j] * (row[a] - (i == a));
                }
            }
        }
        dp = move(next);
    }
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int i = (x1 != x2), j = (y1 != y2);
    cout << (dp[i][j] / row[i] / col[j]).val() << '\n';
    return 0;
}
