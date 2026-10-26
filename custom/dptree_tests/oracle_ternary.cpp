// Exhaustive oracles: subsets of vertices/edges, or assignments to all leaves.
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
struct Edge { int u,v; ll w; };

int main(int argc,char **argv) {
    assert(argc == 2);
    int kind = atoi(argv[1]),n; cin >> n;
    const ll INF = 1LL << 60,MOD = 1000000007;
    if (kind == 28) {
        int target; cin >> target;
        assert(n <= 25);
        vector<int> type(n),leaves,order{0};
        vector<array<int,2>> child(n);
        vector<array<ll,3>> cost(n);
        for (int u = 0; u < n; ++u) {
            cin >> type[u];
            if (type[u] == 0) {
                leaves.push_back(u);
                for (ll &c : cost[u]) cin >> c;
            } else {
                cin >> child[u][0] >> child[u][1];
                --child[u][0]; --child[u][1];
            }
        }
        assert(leaves.size() <= 12);
        for (int i = 0; i < n; ++i) if (type[order[i]])
            for (int v : child[order[i]]) order.push_back(v);
        int ways = 1;
        for (size_t i = 0; i < leaves.size(); ++i) ways *= 3;
        ll answer = INF;
        vector<int> value(n);
        for (int mask = 0; mask < ways; ++mask) {
            int code = mask; ll total = 0;
            for (int u : leaves) {
                value[u] = code%3; code /= 3;
                total += cost[u][value[u]];
            }
            if (total >= answer) continue;
            for (int i = n-1; i >= 0; --i) {
                int u = order[i];
                if (type[u]) {
                    int a = value[child[u][0]],b = value[child[u][1]];
                    value[u] = (type[u] == 1 ? a+b : a*b)%3;
                }
            }
            if (value[0] == target) answer = total;
        }
        cout << answer << '\n';
        return 0;
    }
    assert(n <= 20);
    vector<ll> value(n,0);
    if (kind == 27 || kind == 29) for (ll &x : value) cin >> x;
    vector<Edge> edges;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u,v; ll w = 0; cin >> u >> v; --u; --v;
        if (kind == 29 || kind == 30) cin >> w;
        edges.push_back({u,v,w}); adj[u].push_back(v); adj[v].push_back(u);
    }
    ll answer = kind == 29 ? INF : 0;
    vector<int> parent(n,-1),order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u; order.push_back(v);
        }
    }
    if (kind == 27 || kind == 31) {
        for (unsigned mask = 0; mask < (1U << n); ++mask) {
            if (kind == 27) {
                bool ok = true;
                for (int u = 0; u < n; ++u) {
                    int p = parent[u];
                    if (p == -1 || parent[p] == -1) continue;
                    unsigned three = (1U << u)|(1U << p)|(1U << parent[p]);
                    if ((mask & three) == three) { ok = false; break; }
                }
                if (!ok) continue;
                ll sum = 0;
                for (int u = 0; u < n; ++u) if (mask >> u & 1U) sum += value[u];
                answer = max(answer,sum);
            } else {
                int size = __builtin_popcount(mask);
                if (size == 0 || size%3) continue;
                int inside = 0;
                for (auto e : edges) if ((mask >> e.u & 1U) && (mask >> e.v & 1U)) ++inside;
                // An induced subgraph of a tree is a forest.
                if (inside == size-1) ++answer;
            }
        }
    } else {
        for (unsigned mask = 0; mask < (1U << (n-1)); ++mask) {
            if (kind == 30) {
                vector<int> degree(n,0);
                ll sum = 0; bool ok = true;
                for (int i = 0; i < n-1; ++i) if (mask >> i & 1U) {
                    if (++degree[edges[i].u] > 2 || ++degree[edges[i].v] > 2) {
                        ok = false; break;
                    }
                    sum += edges[i].w;
                }
                if (ok) answer = max(answer,sum);
            } else {
                vector<int> p(n),colors(n,0);
                iota(p.begin(),p.end(),0);
                auto find = [&](int u) { while (p[u] != u) u = p[u]; return u; };
                ll sum = 0;
                for (int i = 0; i < n-1; ++i) {
                    if (mask >> i & 1U) sum += edges[i].w;
                    else p[find(edges[i].u)] = find(edges[i].v);
                }
                if (sum >= answer) continue;
                for (int u = 0; u < n; ++u) colors[find(u)] |= int(value[u]);
                if (std::find(colors.begin(),colors.end(),3) == colors.end()) answer = sum;
            }
        }
    }
    cout << (kind == 31 ? answer%MOD : answer) << '\n';
}
