#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;
struct Edge { int to, next; };
struct Graph {
    std::vector<int> head, indegree;
    std::vector<Edge> edges;
    explicit Graph(int n) : head(n + 1, -1), indegree(n + 1) {}
    int node() {
        head.push_back(-1); indegree.push_back(0);
        return int(head.size()) - 1;
    }
    void add(int u, int v) {
        edges.push_back({v, head[u]}); head[u] = int(edges.size()) - 1;
        ++indegree[v];
    }
};
struct RangeGraph {
    Graph &g;
    std::vector<int> id;
    RangeGraph(Graph &graph, int n) : g(graph), id(4 * n) { build(1, 1, n); }
    void build(int p, int l, int r) {
        if (l == r) { id[p] = l; return; }
        id[p] = g.node();
        int m = (l + r) / 2;
        build(p * 2, l, m); build(p * 2 + 1, m + 1, r);
        g.add(id[p * 2], id[p]); g.add(id[p * 2 + 1], id[p]);
    }
    void link(int p, int l, int r, int ql, int qr, int u) {
        if (ql <= l && r <= qr) { g.add(id[p], u); return; }
        int m = (l + r) / 2;
        if (ql <= m) link(p * 2, l, m, ql, qr, u);
        if (qr > m) link(p * 2 + 1, m + 1, r, ql, qr, u);
    }
};

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n, q; std::cin >> n >> q;
    std::vector<ll> duration(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> duration[i];
    Graph g(n);
    int height = 0;
    while ((1 << height) < n) ++height;
    g.edges.reserve(2 * n + size_t(q) * (2 * height + 1));
    RangeGraph tree(g, n);
    for (int i = 0; i < q; ++i) {
        int l, r, u; std::cin >> l >> r >> u;
        tree.link(1, 1, n, l, r, u);
    }
    std::vector<ll> finish(g.head.size());
    std::vector<int> queue;
    for (int u = 1; u < int(g.head.size()); ++u)
        if (g.indegree[u] == 0) queue.push_back(u);
    ll answer = 0;
    for (size_t at = 0; at < queue.size(); ++at) {
        int u = queue[at];
        if (u <= n) { finish[u] += duration[u]; answer = std::max(answer, finish[u]); }
        for (int e = g.head[u]; e != -1; e = g.edges[e].next) {
            int v = g.edges[e].to;
            finish[v] = std::max(finish[v], finish[u]);
            if (--g.indegree[v] == 0) queue.push_back(v);
        }
    }
    if (queue.size() != g.head.size() - 1) answer = -1;
    std::cout << answer << '\n';
}
