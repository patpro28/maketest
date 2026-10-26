#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n), b(n), sub(n), dist(n), cost(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> parent(n, -1), weight(n), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto [v, w] : adj[u]) if (v != parent[u]) {
            parent[v] = u;
            weight[v] = w;
            dist[v] = dist[u] + w;
            order.push_back(v);
        }
    }
    ll total = 0;
    for (int u = 0; u < n; ++u) {
        total += a[u];
        cost[0] += a[u] * dist[u];
        sub[u] = a[u];
    }
    for (int i = n - 1; i > 0; --i) {
        int u = order[i];
        sub[parent[u]] += sub[u];
    }
    for (int i = 1; i < n; ++i) {
        int u = order[i];
        cost[u] = cost[parent[u]] + (total - 2 * sub[u]) * weight[u];
    }
    int best = 0;
    for (int u = 1; u < n; ++u)
        if (cost[u] + b[u] < cost[best] + b[best]) best = u;
    cout << best + 1 << ' ' << cost[best] + b[best] << '\n';
}
