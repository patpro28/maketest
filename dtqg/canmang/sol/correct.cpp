#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "slope.h"
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll d; cin >> u >> v >> d; --u; --v;
        adj[u].push_back({v, d}); adj[v].push_back({u, d});
    }
    vector<int> parent(n, -1), order{0};
    vector<ll> bound(n);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto [v, d] : adj[u]) if (v != parent[u]) {
            parent[v] = u; bound[v] = d; order.push_back(v);
        }
    }
    vector<unique_ptr<Slope>> f(n);
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i]; f[u] = make_unique<Slope>();
        for (auto [v, d] : adj[u]) if (parent[v] == u) {
            f[v]->window(d, d); f[u]->merge(*f[v]); f[v].reset();
        }
        f[u]->add_abs(a[u]);
    }
    cout << f[0]->minimum << '\n';
}
