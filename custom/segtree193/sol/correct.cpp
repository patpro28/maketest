#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>
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

struct Node { i64 sum = 0; };
Node merge(Node a, Node b) { return {a.sum + b.sum}; }
class SegmentTree {
    int n;
    std::vector<Node> tree;
    void build(int v, int l, int r, const std::vector<Node> &a) {
        if (l == r) { tree[v] = a[l]; return; }
        int m = (l + r) / 2;
        build(v * 2, l, m, a); build(v * 2 + 1, m + 1, r, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    void set(int v, int l, int r, int pos, Node x) {
        if (l == r) { tree[v] = x; return; }
        int m = (l + r) / 2;
        if (pos <= m) set(v * 2, l, m, pos, x);
        else set(v * 2 + 1, m + 1, r, pos, x);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    int first(int v, int l, int r, int ql, int qr) const {
        if (r < ql || qr < l || tree[v].sum == 0) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        int answer = first(v * 2, l, m, ql, qr);
        return answer != -1 ? answer : first(v * 2 + 1, m + 1, r, ql, qr);
    }

public:
    explicit SegmentTree(const std::vector<Node> &a) : n(int(a.size()) - 1), tree(4 * a.size()) { build(1, 1, n, a); }
    void update(int pos, Node x) { set(1, 1, n, pos, x); }
    int first(int l, int r) const { return l > r ? -1 : first(1, 1, n, l, r); }

};
int main() {
    FastInput in; FastOutput out;
    int c, n, q; in >> c >> n >> q;
    std::vector<Node> a(c + 2);
    for (int i = 0; i < n; ++i) { int x; in >> x; ++a[x + 1].sum; }
    SegmentTree tree(a);
    while (q--) {
        int type, x; in >> type >> x;
        if (type == 1) { ++a[x + 1].sum; tree.update(x + 1, a[x + 1]); }
        else {
            int pos = tree.first(x + 1, c + 1);
            out << (pos == -1 ? -1 : pos - 1) << '\n';
            if (pos != -1) {
                --a[pos].sum; tree.update(pos, a[pos]);
                ++a[pos - x].sum; tree.update(pos - x, a[pos - x]);
            }
        }
    }
}
