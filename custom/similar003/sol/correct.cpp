/*
Author: Tu Pham Anh
Date: 2025/07/16 - 16:34
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    ll n, ba = 1, hai = 1; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (x % 2 == 0) (hai *= 2) %= mod;
        (ba *= 3) %= mod;
    }
    cout << (ba - hai + mod) % mod << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}