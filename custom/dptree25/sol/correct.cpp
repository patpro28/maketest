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
    // Selecting u forbids selecting every descendant: exactly one choice.
    vector<array<ll, 2>> dp(n, {1, 1});
    for (int i = n - 1; i > 0; --i) {
        int u = order[i], p = parent[u];
        dp[p][0] = dp[p][0] * ((dp[u][0] + dp[u][1]) % MOD) % MOD;
    }
    cout << (dp[0][0] + dp[0][1]) % MOD << '\n';
}
