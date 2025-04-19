/*
Author: Kiragaya
Date: 2024/10/21 - 19:03
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];
long long depth[N];
int n;
long long ans = 0;

void dfs(int u, int p) {
    depth[u] = 0;
    for (auto &[v, w]: adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        ans = max(ans, depth[u] + depth[v] + w);
        depth[u] = max(depth[u], depth[v] + w);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    dfs(1, 0);
    cout << ans << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}