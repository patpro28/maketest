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

constexpr i64 LIMIT = 1000000000000000000LL;
constexpr i64 CAP = LIMIT + 1;
i64 bounded_lcm(i64 a, i64 b) {
    if (a == CAP || b == CAP) return CAP;
    i64 reduced = a / std::gcd(a, b);
    return reduced > LIMIT / b ? CAP : reduced * b;
}
struct Node { i64 value = 1; };
Node merge(Node a, Node b) { return {bounded_lcm(a.value, b.value)}; }
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
    int first_bad(int v, int l, int r, int start, i64 budget, i64 &acc) const {
        if (r < start) return -1;
        if (start <= l) {
            i64 next = bounded_lcm(acc, tree[v].value);
            if (next <= budget) { acc = next; return -1; }
        }
        if (l == r) return l;
        int m = (l + r) / 2;
        int answer = first_bad(v * 2, l, m, start, budget, acc);
        return answer != -1 ? answer : first_bad(v * 2 + 1, m + 1, r, start, budget, acc);
    }

public:
    explicit SegmentTree(const std::vector<Node> &a) : n(int(a.size()) - 1), tree(4 * a.size()) { build(1, 1, n, a); }
    void update(int pos, Node x) { set(1, 1, n, pos, x); }
    int farthest(int start, i64 budget) const {
        i64 acc = 1; int bad = first_bad(1, 1, n, start, budget, acc);
        return bad == -1 ? n : bad - 1;
    }

};
int main() {
    FastInput in; FastOutput out;
    int n, q; in >> n >> q;
    std::vector<Node> a(n + 1);
    for (int i = 1; i <= n; ++i) in >> a[i].value;
    SegmentTree tree(a);
    while (q--) {
        int type, l; i64 x; in >> type >> l >> x;
        if (type == 1) tree.update(l, {x});
        else out << tree.farthest(l, x) << '\n';
    }
}
