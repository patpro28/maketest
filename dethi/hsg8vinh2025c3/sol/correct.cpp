/*
Author: Tu Pham Anh
Date: 2025/04/15 - 20:52
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 1e6 + 1;
vector<int> price, a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, p; cin >> n >> p;
    price.assign(N, p + 1);
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        price[a[i]] = min(price[a[i]], x);
    }
    sort(price.begin(), price.end());
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (price[i] <= p) {
            p -= price[i];
            ans++;
        }
    }
    cout << ans;

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}