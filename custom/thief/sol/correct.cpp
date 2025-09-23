/*
Author: Kiragaya
Date: 2024/10/20 - 09:14
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
using item = pair<int, int>;

bool minimize(long long &a, long long b) { return a > b ? a = b, true : false; }

const int MAXC = 1e5 + 5;

long long dp[MAXC][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, w, h;
    cin >> n >> w >> h;
    vector<item> a(n);
    int sumC = 0;
    for (auto &[x, y] : a) {
        cin >> x >> y;
        sumC += y;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (auto &[w, c]: a) {
        for (int i = sumC; i >= c; --i) {
            minimize(dp[i][0], dp[i - c][0] + w);
            minimize(dp[i][1], dp[i - c][1] + w);
            if (w <= h) minimize(dp[i][1], dp[i - c][0]);
        }
    }

    long long ans = 0;
    for (int i = sumC; i >= 0; --i) {
        if (dp[i][0] <= w || dp[i][1] <= w) {
            ans = i;
            break;
        }
    }
    cout << ans << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}
