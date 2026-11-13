#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 20;
const int mod = 1e9 + 7;

int n, m, a[N], b[N];
int dp[1 << N][N];

int cal(int mask, int id, int k, int s) {
    if (k == n) return 1;
    if (s == a[k]) return cal(mask, 0, k + 1, 0);
    if (id == m) return 0;
    if (dp[mask][id] != -1) return dp[mask][id];
    auto &ans = dp[mask][id];
    ans = 0;
    int _mask = ((1 << (m - id)) - (mask >> id) - 1) << id;
    while (_mask) {
        int i = __builtin_ctz(_mask);
        if (s + b[i] <= a[k])
            (ans += cal(mask | 1 << i, i + 1, k, s + b[i])) %= mod;
        else
            break;
        _mask ^= (1 << i);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a, a + n, greater<int>());
        for (int i = 0; i < m; ++i) cin >> b[i];
        sort(b, b + m);
        cout << cal(0, 0, 0, 0) << '\n';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}
