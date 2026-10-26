#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

struct Node {
    long long mn = std::numeric_limits<long long>::max(), mx = std::numeric_limits<long long>::lowest();
};
Node leaf(long long x) { return {x, x}; }
Node merge(const Node &a, const Node &b) { return {std::min(a.mn, b.mn), std::max(a.mx, b.mx)}; }

class SegmentTree {
    int n;
    std::vector<Node> tree;
    void build(int v, int l, int r, const std::vector<long long> &a) {
        if (l == r) { tree[v] = leaf(a[l]); return; }
        int m = (l + r) / 2;
        build(v * 2, l, m, a);
        build(v * 2 + 1, m + 1, r, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    void set(int v, int l, int r, int pos, long long x) {
        if (l == r) { tree[v] = leaf(x); return; }
        int m = (l + r) / 2;
        if (pos <= m) set(v * 2, l, m, pos, x);
        else set(v * 2 + 1, m + 1, r, pos, x);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    int find_bad(int v, int l, int r, int ql, int qr, long long low, long long high) const {
        if (r < ql || qr < l || (tree[v].mn >= low && tree[v].mx <= high)) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        int answer = find_bad(v * 2, l, m, ql, qr, low, high);
        if (answer != -1) return answer;
        return find_bad(v * 2 + 1, m + 1, r, ql, qr, low, high);
    }
public:
    explicit SegmentTree(const std::vector<long long> &a)
        : n(int(a.size()) - 1), tree(4 * a.size()) { build(1, 1, n, a); }
    void update(int pos, long long x) { set(1, 1, n, pos, x); }
    int first_outside(int l, int r, long long low, long long high) const {
        return find_bad(1, 1, n, l, r, low, high);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    SegmentTree tree(a);
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int i; std::cin >> i;
            long long x; std::cin >> x; tree.update(i, x);
        } else {
            int l, r; long long low, high; std::cin >> l >> r >> low >> high;
            std::cout << tree.first_outside(l, r, low, high) << '\n';
        }
    }
}
