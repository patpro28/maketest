#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> value(n);
    for (ll &x : value) cin >> x;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u; order.push_back(v);
        }
    }
    vector<array<ll,3>> dp(n);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        array<ll,3> sum{0,0,0};
        for (int v : adj[u]) if (parent[v] == u)
            for (int t = 0; t < 3; ++t) sum[t] += dp[v][t];
        dp[u][0] = max(sum[0], value[u] + sum[1]);
        dp[u][1] = max(sum[0], value[u] + sum[2]);
        dp[u][2] = sum[0];
    }
    cout << dp[0][0] << '\n';
}
