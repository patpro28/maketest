#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;
struct Edge { int to, next; ll cost; };
struct Graph {
    std::vector<int> head;
    std::vector<Edge> edges;
    explicit Graph(int n) : head(n + 1, -1) {}
    int node() { head.push_back(-1); return int(head.size()) - 1; }
    void add(int u, int v, ll w) {
        edges.push_back({v, head[u], w}); head[u] = int(edges.size()) - 1;
    }
};
struct RangeGraph {
    Graph &g;
    std::vector<int> in, out;
    RangeGraph(Graph &graph, int n) : g(graph), in(4 * n), out(4 * n) { build(1, 1, n); }
    void build(int p, int l, int r) {
        if (l == r) { in[p] = out[p] = l; return; }
        in[p] = g.node(); out[p] = g.node();
        int m = (l + r) / 2;
        build(p * 2, l, m); build(p * 2 + 1, m + 1, r);
        g.add(in[p * 2], in[p], 0); g.add(in[p * 2 + 1], in[p], 0);
        g.add(out[p], out[p * 2], 0); g.add(out[p], out[p * 2 + 1], 0);
    }
    void link(int p, int l, int r, int ql, int qr, int hub, ll c, bool source) {
        if (ql <= l && r <= qr) {
            if (source) g.add(in[p], hub, c);
            else g.add(hub, out[p], 0);
            return;
        }
        int m = (l + r) / 2;
        if (ql <= m) link(p * 2, l, m, ql, qr, hub, c, source);
        if (qr > m) link(p * 2 + 1, m + 1, r, ql, qr, hub, c, source);
    }
};

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n, q, s, t; std::cin >> n >> q >> s >> t;
    Graph g(n);
    int height = 0;
    while ((1 << height) < n) ++height;
    g.edges.reserve(4 * n + size_t(q) * (4 * height + 2));
    RangeGraph tree(g, n);
    for (int i = 0; i < q; ++i) {
        int l, r, a, b; ll c;
        std::cin >> l >> r >> a >> b >> c;
        int hub = g.node();
        tree.link(1, 1, n, l, r, hub, c, true);
        tree.link(1, 1, n, a, b, hub, c, false);
    }
    const ll INF = std::numeric_limits<ll>::max() / 4;
    std::vector<ll> dist(g.head.size(), INF);
    using State = std::pair<ll, int>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> heap;
    dist[s] = 0; heap.push({0, s});
    while (!heap.empty()) {
        auto [d, u] = heap.top(); heap.pop();
        if (d != dist[u]) continue;
        if (u == t) { std::cout << d << '\n'; return 0; }
        for (int e = g.head[u]; e != -1; e = g.edges[e].next) {
            const auto &edge = g.edges[e];
            if (dist[edge.to] > d + edge.cost) {
                dist[edge.to] = d + edge.cost;
                heap.push({dist[edge.to], edge.to});
            }
        }
    }
    std::cout << -1 << '\n';
}
