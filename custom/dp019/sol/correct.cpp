/*
Author: Tu Pham Anh
Date: 2025/11/22 - 17:38
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 2e5 + 5;

long long b[N], c[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n, q; cin >> n >> q;
    while (q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        b[l] += x;
        b[r + 1] -= x + (r - l + 1) * y;
        c[l] += y;
        c[r + 1] -= y;
    }

    for (int i = 1; i <= n; ++i) {
        b[i] += b[i - 1] + c[i - 1];
        c[i] += c[i - 1];
        cout << b[i] << ' ';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}