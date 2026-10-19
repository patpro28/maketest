#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> cost(n);
    for (ll &c : cost) cin >> c;
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
    const ll INF = 1LL << 60;
    // station: u has a station; covered: a child covers u;
    // pending: u has no station and must be covered by its parent.
    vector<ll> station(n), covered(n), pending(n);
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        ll base = 0, extra = INF;
        station[u] = cost[u]; pending[u] = 0;
        for (int v : adj[u]) if (parent[v] == u) {
            station[u] += min({station[v], covered[v], pending[v]});
            pending[u] = min(INF, pending[u] + covered[v]);
            ll best = min(station[v], covered[v]);
            base += best;
            extra = min(extra, station[v] - best);
        }
        // extra forces at least one child to have a station.
        covered[u] = min(INF, base + extra);
    }
    cout << min(station[0], covered[0]) << '\n';
}
