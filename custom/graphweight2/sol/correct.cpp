/*
Author: Tu Pham Anh
Date: 2025/07/25 - 07:52
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
typedef array<int, 3> Edge;

const int N = 1e5;
vector<pair<int, int>> adj[N + 5];
int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    int q; cin >> q;
    while (q--) {
        int u, w; cin >> u >> w;
        int cnt = 0;
        for (auto &[v, weight] : adj[u]) {
            if (weight >= w) {
                cnt++;
            }
        }
        cout << cnt << '\n';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}