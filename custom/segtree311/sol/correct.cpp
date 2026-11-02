#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>
#include <utility>
using i64 = long long;
// Buffered I/O keeps the 0.5-second limit practical at maximum input size.
class FastInput {
    char data[1 << 16];
    int pos = 0, size = 0;
    char get() {
        if (pos == size) { size = int(std::fread(data, 1, sizeof(data), stdin)); pos = 0; }
        return pos < size ? data[pos++] : 0;
    }
public:
    FastInput &operator>>(char &value) {
        value = get(); while (value && value <= ' ') value = get();
        return *this;
    }
    template<class T> FastInput &operator>>(T &value) {
        char c = get(); while (c && c <= ' ') c = get();
        bool negative = c == '-'; if (negative) c = get();
        value = 0;
        while (c >= '0' && c <= '9') { value = value * 10 + c - '0'; c = get(); }
        if (negative) value = -value;
        return *this;
    }
};
class FastOutput {
    char data[1 << 16];
    int size = 0;
    void flush() { std::fwrite(data, 1, size, stdout); size = 0; }
public:
    ~FastOutput() { flush(); }
    FastOutput &operator<<(char c) { if (size == int(sizeof(data))) flush(); data[size++] = c; return *this; }
    FastOutput &operator<<(int x) { return *this << static_cast<long long>(x); }
    FastOutput &operator<<(long long x) {
        if (x < 0) { *this << '-'; x = -x; }
        char digits[24]; int length = 0;
        do { digits[length++] = char('0' + x % 10); x /= 10; } while (x);
        while (length) *this << digits[--length];
        return *this;
    }
};



struct Node {
    i64 sum, prefix, suffix, best;
};
Node leaf(i64 x) { return {x, x, x, x}; }
Node merge(const Node &a, const Node &b) {
    return {a.sum + b.sum,
            std::max(a.prefix, a.sum + b.prefix),
            std::max(b.suffix, b.sum + a.suffix),
            std::max({a.best, b.best, a.suffix + b.prefix})};
}
class SegmentTree {
    int n;
    std::vector<Node> tree;
    void build(int v, int l, int r, const std::vector<i64> &a) {
        if (l == r) { tree[v] = leaf(a[l]); return; }
        int mid = (l + r) / 2;
        build(v * 2, l, mid, a); build(v * 2 + 1, mid + 1, r, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    void update(int v, int l, int r, int pos, i64 value) {
        if (l == r) { tree[v] = leaf(value); return; }
        int mid = (l + r) / 2;
        if (pos <= mid) update(v * 2, l, mid, pos, value);
        else update(v * 2 + 1, mid + 1, r, pos, value);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    Node query(int v, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return tree[v];
        int mid = (l + r) / 2;
        if (qr <= mid) return query(v * 2, l, mid, ql, qr);
        if (ql > mid) return query(v * 2 + 1, mid + 1, r, ql, qr);
        return merge(query(v * 2, l, mid, ql, qr),
                     query(v * 2 + 1, mid + 1, r, ql, qr));
    }
public:
    explicit SegmentTree(const std::vector<i64> &a) : n(int(a.size()) - 1), tree(4 * a.size()) { build(1, 1, n, a); }
    void update(int pos, i64 value) { update(1, 1, n, pos, value); }
    Node query(int l, int r) const { return query(1, 1, n, l, r); }
};
int main() {
    FastInput in; FastOutput out;
    int n; in >> n;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) in >> a[i];
    SegmentTree tree(a);
    int m; in >> m;
    while (m--) {
        int type, x; i64 y; in >> type >> x >> y;
        if (type == 0) tree.update(x, y);
        else out << tree.query(x, int(y)).best << '\n';
    }
}
