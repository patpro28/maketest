/*
Author: Tu Pham Anh
Date: 2025/03/15 - 14:03
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

long long dp[45][500005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m, q, x;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> x;
        for (int j = 1; j <= m; j++) {
            dp[j][i + 1] = dp[j][i] + (x == j);
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        long long res = 1;
        for (int i = 1; i <= m; i++) 
            if (dp[i][r] - dp[i][l - 1] > 0) {
                res *= dp[i][r] - dp[i][l - 1];
                res %= 1000000007;
            }
        cout << res << '\n';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}