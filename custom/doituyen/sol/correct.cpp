#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
struct Edge { int u, v, c, w; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s; --t;
    vector<ll> p(n);
    for (auto &x : p) cin >> x;
    vector<Edge> edges(m);
    vector<pair<int, int>> keys;
    for (auto &e : edges) {
        cin >> e.u >> e.v >> e.c >> e.w;
        --e.u; --e.v;
        keys.push_back({e.u, e.c});
        keys.push_back({e.v, e.c});
    }
    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());
    int k = int(keys.size());
    // Original vertices are transfer hubs; each (city, line) is another vertex.
    vector<vector<pair<int, ll>>> adj(n + k);
    for (int i = 0; i < k; ++i) {
        int u = keys[i].first;
        adj[u].push_back({n + i, 0});
        adj[n + i].push_back({u, p[u]});
    }
    auto id = [&](int u, int c) {
        return n + int(lower_bound(keys.begin(), keys.end(), make_pair(u, c)) - keys.begin());
    };
    for (auto e : edges) adj[id(e.u, e.c)].push_back({id(e.v, e.c), e.w});
    const ll INF = 4000000000000000000LL;
    vector<ll> d(n + k, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    d[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (du != d[u]) continue;
        // Stop on a destination line-state, before paying any transfer fee.
        if (u == t || (u >= n && keys[u - n].first == t)) {
            cout << du << '\n';
            return 0;
        }
        for (auto [v, w] : adj[u]) if (du + w < d[v]) {
            d[v] = du + w;
            pq.push({d[v], v});
        }
    }
    cout << -1 << '\n';
}
