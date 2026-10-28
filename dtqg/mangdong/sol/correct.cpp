#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

struct RollbackDSU {
    struct Change { int a, b; ll pairs; };
    vector<int> parent, size;
    vector<ll> red, blue;
    vector<Change> history;
    ll pairs = 0;
    explicit RollbackDSU(const vector<int>& color) : parent(color.size()),
        size(color.size(), 1), red(color.size()), blue(color.size()) {
        iota(parent.begin(), parent.end(), 0);
        for (int i = 0; i < int(color.size()); ++i) {
            red[i] = color[i] == 0;
            blue[i] = color[i] == 1;
        }
    }
    int find(int u) const {
        while (parent[u] != u) u = parent[u];
        return u;
    }
    void unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;
        if (size[u] < size[v]) swap(u, v);
        history.push_back({u, v, pairs});
        pairs += red[u] * blue[v] + red[v] * blue[u];
        parent[v] = u;
        size[u] += size[v]; red[u] += red[v]; blue[u] += blue[v];
    }
    void rollback(int snapshot) {
        while (int(history.size()) > snapshot) {
            auto change = history.back(); history.pop_back();
            int u = change.a, v = change.b;
            parent[v] = v;
            size[u] -= size[v]; red[u] -= red[v]; blue[u] -= blue[v];
            pairs = change.pairs;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> color(n);
    for (auto &x : color) cin >> x;
    vector<char> operation(q);
    vector<vector<pair<int, int>>> tree(4 * q);
    auto add = [&](auto&& self, int node, int l, int r, int a, int b, pair<int, int> edge) -> void {
        if (a > r || b < l) return;
        if (a <= l && r <= b) { tree[node].push_back(edge); return; }
        int mid = (l + r) / 2;
        self(self, node * 2, l, mid, a, b, edge);
        self(self, node * 2 + 1, mid + 1, r, a, b, edge);
    };
    map<pair<int, int>, int> active;
    for (int i = 0; i < q; ++i) {
        cin >> operation[i];
        if (operation[i] == '?') continue;
        int u, v; cin >> u >> v; --u; --v;
        if (u > v) swap(u, v);
        pair<int, int> edge{u, v};
        if (operation[i] == '+') active[edge] = i;
        else {
            add(add, 1, 0, q - 1, active.at(edge), i - 1, edge);
            active.erase(edge);
        }
    }
    for (auto [edge, start] : active) add(add, 1, 0, q - 1, start, q - 1, edge);
    RollbackDSU dsu(color);
    auto solve = [&](auto&& self, int node, int l, int r) -> void {
        int snapshot = int(dsu.history.size());
        for (auto [u, v] : tree[node]) dsu.unite(u, v);
        if (l == r) {
            if (operation[l] == '?') cout << dsu.pairs << '\n';
        } else {
            int mid = (l + r) / 2;
            self(self, node * 2, l, mid);
            self(self, node * 2 + 1, mid + 1, r);
        }
        dsu.rollback(snapshot);
    };
    solve(solve, 1, 0, q - 1);
}
