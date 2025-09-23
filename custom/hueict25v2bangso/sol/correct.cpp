/*
Author: Tu Pham Anh
Date: 2025/06/19 - 19:54
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;
const ll inv2 = 5e8 + 4;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    ll n;
    cin >> n;
    ll begin = ((2 + 2 * n) * n / 2) % MOD;
    ll diff = 2 * n;
    ll end = (begin + diff * (n - 1)) % MOD; // last element
    ll ans = (begin + end) * n % MOD * inv2 % MOD; // sum of arithmetic sequence
    cout << ans << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}