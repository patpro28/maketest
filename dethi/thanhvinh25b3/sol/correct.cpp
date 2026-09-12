/*
Author: Tu Pham Anh
Date: 2025/10/15 - 18:45
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k; cin >> n >> k;
    long long a[n + 1] = {};
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    long long ans = 0;
    for (int i = 0; i <= k; ++i) 
        ans = max(ans, a[i] + a[n] - a[n - (k - i)]);
    cout << ans << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}