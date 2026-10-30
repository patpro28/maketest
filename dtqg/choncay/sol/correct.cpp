#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll NEG = -4000000000000000000LL;
struct Matrix {
    ll a[2][2];
    explicit Matrix(bool identity = false) {
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j)
            a[i][j] = identity && i == j ? 0 : NEG;
    }
};
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 2; ++i) for (int k = 0; k < 2; ++k) if (a.a[i][k] != NEG)
        for (int j = 0; j < 2; ++j) if (b.a[k][j] != NEG)
            c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
    return c;
}
struct SegmentTree {
    int size;
    vector<Matrix> tree;
    explicit SegmentTree(int n) : size(1) {
        while (size < n) size *= 2;
        tree.assign(2*size, Matrix(true));
    }
    void set(int p, Matrix value) {
        p += size; tree[p] = value;
        while (p >>= 1) tree[p] = multiply(tree[2*p], tree[2*p+1]);
    }
    Matrix query(int l, int r) const {
        Matrix left(true), right(true);
        for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = multiply(left, tree[l++]);
            if (r & 1) right = multiply(tree[--r], right);
        }
        return multiply(left, right);
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> w(n+1), f0(n+1), f1(n+1), g0(n+1), g1(n+1);
    for (int i = 1; i <= n; ++i) cin >> w[i];
    vector<vector<int>> adj(n+1);
    for (int i = 1; i < n; ++i) { int u,v; cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u); }
    vector<int> parent(n+1), order{1}, size(n+1,1), heavy(n+1), top(n+1), pos(n+1), tail(n+1);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) { parent[v] = u; order.push_back(v); }
    }
    for (int i = n-1; i >= 0; --i) {
        int u = order[i]; f1[u] = w[u];
        for (int v : adj[u]) if (parent[v] == u) {
            size[u] += size[v]; f0[u] += max(f0[v],f1[v]); f1[u] += f0[v];
            if (!heavy[u] || size[v] > size[heavy[u]]) heavy[u] = v;
        }
        g0[u] = f0[u] - max(f0[heavy[u]],f1[heavy[u]]);
        g1[u] = f1[u] - f0[heavy[u]];
    }
    int timer = 0; vector<int> heads{1};
    while (!heads.empty()) {
        int head = heads.back(); heads.pop_back();
        for (int u = head; u; u = heavy[u]) {
            top[u] = head; pos[u] = timer++;
            for (int v : adj[u]) if (parent[v] == u && v != heavy[u]) heads.push_back(v);
        }
        tail[head] = timer;
    }
    auto matrix = [&](int u) {
        Matrix m; m.a[0][0] = m.a[0][1] = g0[u]; m.a[1][0] = g1[u]; return m;
    };
    SegmentTree seg(n);
    for (int u = 1; u <= n; ++u) seg.tree[seg.size+pos[u]] = matrix(u);
    for (int i = seg.size-1; i; --i) seg.tree[i] = multiply(seg.tree[2*i],seg.tree[2*i+1]);
    auto chain = [&](int head) {
        Matrix m = seg.query(pos[head],tail[head]);
        return array<ll,2>{max(m.a[0][0],m.a[0][1]),max(m.a[1][0],m.a[1][1])};
    };
    while (q--) {
        int u; ll x; cin >> u >> x;
        g1[u] += x-w[u]; w[u] = x;
        for (int v = u; v; ) {
            int head = top[v]; auto before = chain(head);
            seg.set(pos[v],matrix(v)); auto after = chain(head);
            int p = parent[head];
            if (!p) break;
            g0[p] += max(after[0],after[1])-max(before[0],before[1]);
            g1[p] += after[0]-before[0]; v = p;
        }
        auto result = chain(1); cout << max(result[0],result[1]) << '\n';
    }
}
