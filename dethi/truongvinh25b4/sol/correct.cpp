/*
Author: Tu Pham Anh
Date: 2025/10/04 - 17:34
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
    int n, q;
    cin >> n >> q;
    map<int, int> last, ans;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (last.count(x)) {
            ans[x] = min(ans[x], i - last[x]);
        } else ans[x] = n + 1;
        last[x] = i;
    }
    while (q--) {
        int x; cin >> x;
        if (!ans.count(x) || ans[x] == n + 1) cout << 0 << "\n";
        else cout << ans[x] << "\n";
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}