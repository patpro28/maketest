/*
Author: Tu Pham Anh
Date: 2025/07/15 - 07:45
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s; cin >> s;
        string p = s;
        for (int i = 0; i < n; ++i)
            if (s[i] == '1') {
                p[i] = '0';
                if (i > 0 and s[i - 1] == '0') p[i - 1] = '1';
                if (i < n - 1 and s[i + 1] == '0') p[i + 1] = '1';
            }
        k--; s = p;
        vector<int> f(n, 1e9);
        int first = -1e9;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') first = i;
            f[i] = min(f[i], i - first);
        }
        first = 1e9;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '1') first = i;
            f[i] = min(f[i], first - i);
        }
        for (int i = 0; i < n; ++i)
            if (f[i] > k) s[i] = '0';
            else s[i] = (k - f[i]) & 1 ? '0' : '1';
        cout << s << '\n';
    }

    return 0;
}