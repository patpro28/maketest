#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    // Reverse traversal order processes every child before its parent.
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u; order.push_back(v);
        }
    }
    const ll MOD = 1000000007;
    // dp[u][0/1]: u is matched to zero/exactly one child.
    vector<array<ll, 2>> dp(n, {1, 0});
    for (int i = n - 1; i > 0; --i) {
        int u = order[i], p = parent[u];
        ll total = (dp[u][0] + dp[u][1]) % MOD;
        // Keep the old dp[p][0] when adding the edge (p,u).
        ll new_one = (dp[p][1] * total + dp[p][0] * dp[u][0]) % MOD;
        dp[p][0] = dp[p][0] * total % MOD;
        dp[p][1] = new_one;
    }
    cout << (dp[0][0] + dp[0][1]) % MOD << '\n';
}
