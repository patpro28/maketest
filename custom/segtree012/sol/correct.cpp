#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

struct Node {
    long long income = 0, expense = 0;
};
Node leaf(long long x) {
    return {std::max(x, 0LL), std::max(-x, 0LL)};
}
Node merge(const Node &a, const Node &b) {
    return {a.income + b.income, a.expense + b.expense};
}

class SegmentTree {
    std::vector<Node> tree;
    void build(int v, int l, int r, const std::vector<long long> &a) {
        if (l == r) { tree[v] = leaf(a[l]); return; }
        int m = (l + r) / 2;
        build(v * 2, l, m, a);
        build(v * 2 + 1, m + 1, r, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
public:
    explicit SegmentTree(const std::vector<long long> &a) : tree(4 * a.size()) {
        build(1, 1, int(a.size()) - 1, a);
    }
    void update(int v, int l, int r, int pos, long long x) {
        if (l == r) { tree[v] = leaf(x); return; }
        int m = (l + r) / 2;
        if (pos <= m) update(v * 2, l, m, pos, x);
        else update(v * 2 + 1, m + 1, r, pos, x);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    Node query(int v, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return Node{};
        if (ql <= l && r <= qr) return tree[v];
        int m = (l + r) / 2;
        return merge(query(v * 2, l, m, ql, qr),
                     query(v * 2 + 1, m + 1, r, ql, qr));
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    SegmentTree tree(a);
    while (q--) {
        int type, i;
        std::cin >> type >> i;
        if (type == 1) {
            long long x;
            std::cin >> x;
            tree.update(1, 1, n, i, x);
        } else {
            int r;
            std::cin >> r;
            Node result = tree.query(1, 1, n, i, r);
            std::cout << result.income << ' ' << result.expense << '\n';
        }
    }
}
