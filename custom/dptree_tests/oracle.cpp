// Independent exhaustive oracle; intentionally limited to small trees.
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
    int kind = atoi(argv[1]), n;
    cin >> n;
    assert(1 <= n && n <= 20);
    vector<ll> a(n, 0);
    if (kind == 18 || kind == 22) for (ll &x : a) cin >> x;
    vector<Edge> edges;
    vector<unsigned> adjacent(n, 0);
    vector<int> degree(n, 0);
    for (int i = 1; i < n; ++i) {
        int u, v; ll w = 0; cin >> u >> v; --u; --v;
        if (kind == 19) cin >> w;
        edges.push_back({u, v, w});
        adjacent[u] |= 1U << v; adjacent[v] |= 1U << u;
        ++degree[u]; ++degree[v];
    }
    const ll INF = 1LL << 60;
    ll answer = kind == 18 ? -INF : kind == 17 ? 0 : INF;
    if (kind == 19) {
        // Enumerate cut edges, then reconstruct connectivity from scratch.
        for (unsigned cut = 0; cut < (1U << (n - 1)); ++cut) {
            vector<int> p(n);
            iota(p.begin(), p.end(), 0);
            auto find = [&](int u) {
                while (p[u] != u) u = p[u];
                return u;
            };
            ll cost = 0;
            for (int i = 0; i < n - 1; ++i) {
                if (cut >> i & 1U) cost += edges[i].w;
                else p[find(edges[i].u)] = find(edges[i].v);
            }
            if (cost >= answer) continue;
            bool ok = true;
            for (int u = 1; u < n; ++u)
                if (degree[u] == 1 && find(u) == find(0)) ok = false;
            if (ok) answer = cost;
        }
    } else {
        unsigned size = 1U << n;
        vector<ll> sum(size, 0);
        vector<unsigned> cover(size, 0);
        vector<int> inside(size, 0);
        for (unsigned mask = 0; mask < size; ++mask) {
            if (mask) {
                int u = __builtin_ctz(mask);
                unsigned rest = mask & (mask - 1);
                sum[mask] = sum[rest] + a[u];
                inside[mask] = inside[rest] + __builtin_popcount(adjacent[u] & rest);
                cover[mask] = cover[rest] | adjacent[u] | (1U << u);
            }
            if (kind == 17) {
                if (inside[mask] == 0) ++answer;
            } else if (kind == 18) {
                // Every induced subgraph of a tree is a forest.
                if (mask && inside[mask] == __builtin_popcount(mask) - 1)
                    answer = max(answer, sum[mask]);
            } else if (kind == 22 && cover[mask] == size - 1) {
                answer = min(answer, sum[mask]);
            }
        }
    }
    cout << (kind == 17 ? answer % 1000000007 : answer) << '\n';
}
