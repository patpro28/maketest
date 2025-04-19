/*
Author: Tu Pham Anh
Date: 2024/12/26 - 17:29
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

pair<int, int> pos[2000000 + 10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            pos[x] = {i + 1, j + 1};
        }
    while (q--) {
        int x;
        cin >> x;
        if (pos[x].first == 0) {
            cout << "-1\n";
        } else {
            cout << pos[x].first << ' ' << pos[x].second << '\n';
        }
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}