/*
Author: Tu Pham Anh
Date: 2026/04/06 - 18:18
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n, k, d;
    cin >> n >> k >> d;
    long long dp[n + 1][k + 1];
    long long a[n + 1], w[k + 1];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= k; ++i) cin >> w[i];

    memset(dp, -0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i][1] = max(dp[i - 1][1], a[i] * w[1]);
        for (int j = 2; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (i - d >= 0) dp[i][j] = max(dp[i][j], dp[i - d][j - 1] + a[i] * w[j]);
        }
    }
    if (dp[n][k] < -1e18) cout << "-1\n";
    else cout << dp[n][k] << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}