/*
Author: Tu Pham Anh
Date: 2025/10/04 - 17:21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int fight(int a, int b) {
    if (a > b) return 3;
    if (a == b) return 1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int a, b; cin >> a >> b;
    int c, d; cin >> c >> d;
    int ans = fight(a, c) + fight(b, d);
    ans = max(ans, fight(a, d) + fight(b, c));
    cout << ans << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}