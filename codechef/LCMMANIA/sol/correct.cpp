/*
Author: Tu Pham Anh
Date: 2025/07/28 - 08:32
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
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int k = 0;
        while (n % 2 == 0) {
            n /= 2;
            k++;
        }
        if (n == 1) {
            cout << "-1 -1 -1" << '\n';
        } else {
            n /= 2;
            k = 1 << k;
            cout << k * n << ' ' << k << ' ' << k << '\n';
        }
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}