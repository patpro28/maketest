#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<array<ll, 2>> dp(n);
    for (auto &state : dp) cin >> state[0] >> state[1];
    struct Edge { int to; ll weight; };
    vector<vector<Edge>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll w; cin >> u >> v >> w; --u; --v;
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
    }
    vector<int> parent(n, -1), order{0};
    vector<ll> weight(n);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto e : adj[u]) if (e.to != parent[u]) {
            parent[e.to] = u; weight[e.to] = e.weight;
            order.push_back(e.to);
        }
    }
    for (int i = n - 1; i > 0; --i) {
        int u = order[i], p = parent[u];
        dp[p][0] += min(dp[u][0], dp[u][1] + weight[u]);
        dp[p][1] += min(dp[u][1], dp[u][0] + weight[u]);
    }
    cout << min(dp[0][0], dp[0][1]) << '\n';
}
