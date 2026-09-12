/*
Author: Tu Pham Anh
Date: 2025/10/11 - 15:22
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
    int n;
    cin >> n;
    vector<int> a(n);
    int mi = INT_MAX;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mi = min(mi, x);
        a[i] = mi;
    }

    int q; cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        // Find number of elements in a[l..r] that are equal to x
        auto it1 = lower_bound(a.begin() + l, a.begin() + r + 1, x, greater<int>());
        auto it2 = upper_bound(a.begin() + l, a.begin() + r + 1, x, greater<int>());
        cout << it2 - it1 << "\n";
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}