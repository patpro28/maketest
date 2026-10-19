#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
#include <utility>
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll w; cin >> u >> v >> w; --u; --v;
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
    }
    vector<int> parent(n, -1), order{0};
    vector<ll> edge_cost(n);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto [v, w] : adj[u]) if (v != parent[u]) {
            parent[v] = u; edge_cost[v] = w;
            order.push_back(v);
        }
    }
    const ll INF = 1LL << 60;
    vector<ll> dp(n, 0);
    for (int i = n - 1; i > 0; --i) {
        int u = order[i];
        if (adj[u].size() == 1) dp[u] = INF;
        dp[parent[u]] += min(edge_cost[u], dp[u]);
    }
    cout << dp[0] << '\n';
}
