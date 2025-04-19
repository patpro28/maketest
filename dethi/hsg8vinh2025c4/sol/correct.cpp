/*
Author: Tu Pham Anh
Date: 2025/04/15 - 21:20
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
    int n, l, r; cin >> n >> l >> r;
    --l, --r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans1 = 0, ans2 = 0;
    map<int, int> mp[2];
    for (int i = 0; i < n; ++i) {
        if (l <= i && i <= r) mp[1][a[i]]++;
        else mp[0][a[i]]++;
    }
    for (auto p : mp[0]) {
        ans1 = max(ans1, p.second);
    }
    for (auto p : mp[1]) {
        ans2 = max(ans2, p.second);
    }
    cout << ans1 + ans2 << endl;
    return 0;
}