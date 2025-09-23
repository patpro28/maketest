/*
Author: Tu Pham Anh
Date: 2025/08/10 - 17:14
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 1000;
int a[N + 1][N + 1];
pair<int, int> pos[N * N + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    fill(pos, pos + N * N + 1, make_pair(n + 1, n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            pos[a[i][j]] = min(pos[a[i][j]], {i, j});
        }
    }
    while (q--) {
        int x;
        cin >> x;
        if (pos[x].first > n) {
            cout << "-1\n";
        } else {
            cout << pos[x].first + 1 << ' ' << pos[x].second + 1 << '\n';
        }
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}