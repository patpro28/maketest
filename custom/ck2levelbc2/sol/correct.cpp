/*
Author: Tu Pham Anh
Date: 2025/05/16 - 20:06
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

namespace D {
    int n, m;
    int dp[5005];

    int main() {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            int w, v;
            cin >> w >> v;
            for (int j = m; j >= w; --j)
                dp[j] = max(dp[j], dp[j - w] + v);
        }
        cout << dp[m];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}