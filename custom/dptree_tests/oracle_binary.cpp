// Exhaustive reference algorithms, independent of the tree DP transitions.
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
struct Edge { int u, v; ll w; };

int main(int argc, char **argv) {
    assert(argc == 2);
    int kind = atoi(argv[1]), n; cin >> n;
    assert(1 <= n && n <= 20 && 23 <= kind && kind <= 26);
    vector<ll> a(n, 0), b(n, 0);
    if (kind == 23) for (ll &x : a) cin >> x;
    if (kind == 24) for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    vector<Edge> edges;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll w = 0; cin >> u >> v; --u; --v;
        if (kind == 24) cin >> w;
        edges.push_back({u, v, w});
        adj[u].push_back(v); adj[v].push_back(u);
    }
    const ll MOD = 1000000007, INF = 1LL << 60;
    ll answer = kind <= 24 ? INF : 0;
    if (kind == 26) {
        for (unsigned mask = 0; mask < (1U << (n - 1)); ++mask) {
            unsigned used = 0;
            bool ok = true;
            for (int i = 0; i < n - 1; ++i) if (mask >> i & 1U) {
                unsigned ends = (1U << edges[i].u) | (1U << edges[i].v);
                if (used & ends) { ok = false; break; }
                used |= ends;
            }
            if (ok) ++answer;
        }
    } else {
        vector<unsigned> ancestors(n, 0);
        if (kind == 25) {
            vector<int> parent(n, -1), order{0};
            for (int i = 0; i < n; ++i) {
                int u = order[i];
                for (int v : adj[u]) if (v != parent[u]) {
                    parent[v] = u;
                    ancestors[v] = ancestors[u] | (1U << u);
                    order.push_back(v);
                }
            }
        }
        for (unsigned mask = 0; mask < (1U << n); ++mask) {
            if (kind == 23) {
                bool ok = true;
                for (auto e : edges)
                    if (!(mask >> e.u & 1U) && !(mask >> e.v & 1U)) {
                        ok = false; break;
                    }
                if (!ok) continue;
                ll cost = 0;
                for (int i = 0; i < n; ++i) if (mask >> i & 1U) cost += a[i];
                answer = min(answer, cost);
            } else if (kind == 24) {
                ll cost = 0;
                for (int i = 0; i < n; ++i) cost += mask >> i & 1U ? b[i] : a[i];
                for (auto e : edges)
                    if (((mask >> e.u) ^ (mask >> e.v)) & 1U) cost += e.w;
                answer = min(answer, cost);
            } else {
                bool ok = true;
                for (int i = 0; i < n; ++i)
                    if ((mask >> i & 1U) && (ancestors[i] & mask)) {
                        ok = false; break;
                    }
                if (ok) ++answer;
            }
        }
    }
    cout << (kind >= 25 ? answer % MOD : answer) << '\n';
}
