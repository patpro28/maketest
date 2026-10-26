#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

struct Node {
    long long sum = 0;
};
Node leaf(long long x) { return {x}; }
Node merge(const Node &a, const Node &b) { return {a.sum + b.sum}; }

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
    int find_prefix(int v, int l, int r, long long target) const {
        if (l == r) return l;
        int m = (l + r) / 2;
        if (tree[v * 2].sum >= target) return find_prefix(v * 2, l, m, target);
        return find_prefix(v * 2 + 1, m + 1, r, target - tree[v * 2].sum);
    }
public:
    explicit SegmentTree(const std::vector<long long> &a)
        : n(int(a.size()) - 1), tree(4 * a.size()) { build(1, 1, n, a); }
    void update(int pos, long long x) { set(1, 1, n, pos, x); }
    int reach(long long target) const {
        return tree[1].sum < target ? -1 : find_prefix(1, 1, n, target);
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
            long long target; std::cin >> target; std::cout << tree.reach(target) << '\n';
        }
    }
}
