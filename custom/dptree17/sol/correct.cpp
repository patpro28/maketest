#include <algorithm>
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
    // Iterative traversal: processing this order backwards handles children first.
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u;
            order.push_back(v);
        }
    }
    const ll MOD = 1000000007;
    vector<ll> skip(n, 1), take(n, 1);
    for (int i = n - 1; i > 0; --i) {
        int u = order[i], p = parent[u];
        skip[p] = skip[p] * ((skip[u] + take[u]) % MOD) % MOD;
        take[p] = take[p] * skip[u] % MOD;
    }
    cout << (skip[0] + take[0]) % MOD << '\n';
}
