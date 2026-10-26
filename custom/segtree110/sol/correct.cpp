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
    int find_other(int v, int l, int r, long long c, bool last) const {
        if (tree[v].mn == c && tree[v].mx == c) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        if (last) {
            int answer = find_other(v * 2 + 1, m + 1, r, c, true);
            return answer == -1 ? find_other(v * 2, l, m, c, true) : answer;
        }
        int answer = find_other(v * 2, l, m, c, false);
        return answer == -1 ? find_other(v * 2 + 1, m + 1, r, c, false) : answer;
    }
public:
    explicit SegmentTree(const std::vector<long long> &a)
        : n(int(a.size()) - 1), tree(4 * a.size()) { build(1, 1, n, a); }
    void update(int pos, long long x) { set(1, 1, n, pos, x); }
    std::pair<int, int> other_ends(long long c) const {
        return {find_other(1, 1, n, c, false), find_other(1, 1, n, c, true)};
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
            long long c; std::cin >> c;
            auto answer = tree.other_ends(c);
            std::cout << answer.first << ' ' << answer.second << '\n';
        }
    }
}
