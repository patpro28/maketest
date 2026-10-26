#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    struct Edge { int to; ll weight; };
    vector<vector<Edge>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll w; cin >> u >> v >> w; --u; --v;
        adj[u].push_back({v,w}); adj[v].push_back({u,w});
    }
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto e : adj[u]) if (e.to != parent[u]) {
            parent[e.to] = u; order.push_back(e.to);
        }
    }
    const ll NEG = -(1LL << 60);
    vector<array<ll,3>> dp(n);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        dp[u] = {0,NEG,NEG};
        for (auto e : adj[u]) if (parent[e.to] == u) {
            int v = e.to;
            ll skip = max({dp[v][0],dp[v][1],dp[v][2]});
            ll take = e.weight + max(dp[v][0],dp[v][1]);
            array<ll,3> next{NEG,NEG,NEG};
            for (int k = 0; k < 3; ++k) if (dp[u][k] != NEG) {
                next[k] = max(next[k], dp[u][k] + skip);
                if (k < 2) next[k+1] = max(next[k+1], dp[u][k] + take);
            }
            dp[u] = next;
        }
    }
    cout << max({dp[0][0],dp[0][1],dp[0][2]}) << '\n';
}
