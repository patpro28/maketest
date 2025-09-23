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
vector<Edge> edges;
int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].emplace_back(v, w);
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        if (a[2] != b[2]) 
            return a[2] < b[2];
        if (a[0] != b[0]) 
            return a[0] < b[0];
        return a[1] < b[1];
    });

    for (int i = 0; i < m; ++i) {
        cout << edges[i][0] << ' ' << edges[i][1] << ' ' << edges[i][2] << '\n';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}