/*
Author: Tu Pham Anh
Date: 2024/11/04 - 08:34
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int binpow(int a, long long n, int mod) {
    int res = 1;
    for (; n; n >>= 1) {
        if (n & 1) {
            res = (1LL * res * a) % mod;
        }
        a = (1LL * a * a) % mod;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    long long k;
    cin >> n >> k;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    vector<bool> vis(n + 1, false);
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        vector<int> cycle;
        int j = i;
        do {
            cycle.push_back(j);
            vis[j] = true;
            j = p[p[j]];
        } while (j != i);
        int len = cycle.size();
        int jump = binpow(2, k - 1, len);
        for (int i = 0; i < len; ++i) {
            ans[cycle[i]] = cycle[(i + jump) % len];
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}
// 18 23 16 24 21 10 2 27 19 7 12 8 13 5 15 26 17 4 3 9 1 22 25 14 28 11 29 6 20
