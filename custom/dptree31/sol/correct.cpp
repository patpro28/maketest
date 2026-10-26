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
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u; order.push_back(v);
        }
    }
    const ll MOD = 1000000007;
    vector<array<ll,3>> dp(n);
    ll answer = 0;
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        dp[u] = {0,1,0}; // Choose only u.
        for (int v : adj[u]) if (parent[v] == u) {
            array<ll,3> next = dp[u]; // Choose nothing from this branch.
            for (int a = 0; a < 3; ++a) for (int b = 0; b < 3; ++b) {
                int r = (a+b) % 3;
                next[r] = (next[r] + dp[u][a] * dp[v][b]) % MOD;
            }
            dp[u] = next;
        }
        answer = (answer + dp[u][0]) % MOD;
    }
    cout << answer << '\n';
}
