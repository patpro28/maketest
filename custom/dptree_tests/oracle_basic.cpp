// Definition-based small oracles; Euler/range-query/DAG oracles for large data.
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main(int argc,char **argv) {
    assert(argc == 2 || argc == 3);
    int kind = atoi(argv[1]),n;
    cin >> n;
    vector<ll> value(n,0);
    if (kind == 32 || kind == 34 || kind == 35) for (ll &x : value) cin >> x;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u,v; cin >> u >> v; --u; --v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    vector<int> parent(n,-1),depth(n,0),order{0},leaf(n,1);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            leaf[u] = 0; parent[v] = u; depth[v] = depth[u]+1; order.push_back(v);
        }
    }
    const ll INF = 1LL << 60,MOD = 1000000007;
    bool direct = n <= 20 && argc == 2;
    if (direct) {
        if (kind == 32 || kind == 33) {
            vector<ll> answer(n);
            for (int u = 0; u < n; ++u) {
                vector<int> descendants{u};
                for (size_t i = 0; i < descendants.size(); ++i) {
                    int v = descendants[i];
                    if (kind == 32) answer[u] += value[v];
                    else answer[u] = max(answer[u],ll(depth[v]-depth[u]));
                    for (int w : adj[v]) if (parent[w] == v) descendants.push_back(w);
                }
            }
            for (int u = 0; u < n; ++u) cout << (u ? " " : "") << answer[u];
            cout << '\n'; return 0;
        }
        if (kind == 35 || kind == 36) {
            vector<unsigned> path(n);
            for (int u : order) path[u] = (1U << u)|(parent[u] == -1 ? 0U : path[parent[u]]);
            ll answer = kind == 35 ? INF : 0;
            for (unsigned mask = 0; mask < (1U << n); ++mask) {
                if (kind == 35) {
                    ll cost = 0;
                    for (int u = 0; u < n; ++u) if (mask >> u & 1U) cost += value[u];
                    if (cost >= answer) continue;
                    bool ok = true;
                    for (int u = 0; u < n; ++u)
                        if (leaf[u] && !(path[u]&mask)) { ok = false; break; }
                    if (ok) answer = cost;
                } else {
                    if (!(mask&1U)) continue;
                    bool ok = true;
                    for (int u = 1; u < n; ++u)
                        if ((mask >> u & 1U) && !(mask >> parent[u] & 1U)) {
                            ok = false; break;
                        }
                    if (ok) ++answer;
                }
            }
            cout << (kind == 36 ? answer%MOD : answer) << '\n';
            return 0;
        }
    }
    if (kind == 34) {
        // Compute every root-to-vertex prefix sum, then examine only leaves.
        vector<ll> sum(n);
        sum[0] = value[0];
        ll answer = -INF;
        for (int u : order) {
            if (u) sum[u] = sum[parent[u]]+value[u];
            if (leaf[u]) answer = max(answer,sum[u]);
        }
        cout << answer << '\n'; return 0;
    }
    assert(kind != 36); // Counting oracle intentionally enumerates subsets only.
    vector<int> tin(n),tout(n),next(n,0),stack{0},euler;
    while (!stack.empty()) {
        int u = stack.back();
        if (next[u] == 0) {
            tin[u] = int(euler.size());
            euler.push_back(u);
        }
        if (next[u] < int(adj[u].size())) {
            int v = adj[u][next[u]++];
            if (v != parent[u]) stack.push_back(v);
        } else {
            tout[u] = int(euler.size());
            stack.pop_back();
        }
    }
    if (kind == 32) {
        vector<ll> prefix(n+1,0);
        for (int i = 0; i < n; ++i) prefix[i+1] = prefix[i]+value[euler[i]];
        for (int u = 0; u < n; ++u)
            cout << (u ? " " : "") << prefix[tout[u]]-prefix[tin[u]];
        cout << '\n';
    } else if (kind == 33) {
        int size = 1;
        while (size < n) size *= 2;
        vector<int> segment(2*size,0);
        for (int i = 0; i < n; ++i) segment[size+i] = depth[euler[i]];
        for (int i = size-1; i; --i) segment[i] = max(segment[2*i],segment[2*i+1]);
        for (int u = 0; u < n; ++u) {
            int l = tin[u]+size,r = tout[u]+size,best = 0;
            while (l < r) {
                if (l&1) best = max(best,segment[l++]);
                if (r&1) best = max(best,segment[--r]);
                l /= 2; r /= 2;
            }
            cout << (u ? " " : "") << best-depth[u];
        }
        cout << '\n';
    } else {
        assert(kind == 35);
        // Each hired task covers an interval of leaves in DFS order.
        // Disjoint subtree intervals partition all leaves. Min-cost covering
        // is a shortest path over consecutive leaf-prefix positions.
        vector<int> prefix(n+1,0);
        for (int i = 0; i < n; ++i) prefix[i+1] = prefix[i]+leaf[euler[i]];
        int count = prefix[n];
        vector<vector<pair<int,ll>>> arcs(count);
        for (int u = 0; u < n; ++u) {
            int l = prefix[tin[u]],r = prefix[tout[u]];
            assert(l < r);
            arcs[l].push_back({r,value[u]});
        }
        vector<ll> dist(count+1,INF);
        dist[0] = 0;
        for (int i = 0; i < count; ++i)
            for (auto e : arcs[i]) dist[e.first] = min(dist[e.first],dist[i]+e.second);
        cout << dist[count] << '\n';
    }
}
