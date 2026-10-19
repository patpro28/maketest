#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> dp(n);
    for (ll &a : dp) cin >> a;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    // Iterative traversal: processing this order backwards handles children first.
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u;
            order.push_back(v);
        }
    }
    ll answer = dp[0];
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        answer = max(answer, dp[u]);
        if (parent[u] != -1) dp[parent[u]] += max(0LL, dp[u]);
    }
    cout << answer << '\n';
}
