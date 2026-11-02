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




class SegmentTree {
    int n;
    std::vector<i64> maximum, lazy;
    void build(int v, int l, int r, const std::vector<i64> &a) {
        if (l == r) { maximum[v] = a[l]; return; }
        int mid = (l + r) / 2;
        build(v * 2, l, mid, a); build(v * 2 + 1, mid + 1, r, a);
        maximum[v] = std::max(maximum[v * 2], maximum[v * 2 + 1]);
    }
    void apply(int v, i64 delta) { maximum[v] += delta; lazy[v] += delta; }
    void push(int v) {
        if (lazy[v] == 0) return;
        apply(v * 2, lazy[v]); apply(v * 2 + 1, lazy[v]); lazy[v] = 0;
    }
    void add(int v, int l, int r, int ql, int qr, i64 delta) {
        if (ql <= l && r <= qr) { apply(v, delta); return; }
        push(v);
        int mid = (l + r) / 2;
        if (ql <= mid) add(v * 2, l, mid, ql, qr, delta);
        if (qr > mid) add(v * 2 + 1, mid + 1, r, ql, qr, delta);
        maximum[v] = std::max(maximum[v * 2], maximum[v * 2 + 1]);
    }
    i64 query(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return maximum[v];
        push(v);
        int mid = (l + r) / 2;
        if (qr <= mid) return query(v * 2, l, mid, ql, qr);
        if (ql > mid) return query(v * 2 + 1, mid + 1, r, ql, qr);
        return std::max(query(v * 2, l, mid, ql, qr),
                        query(v * 2 + 1, mid + 1, r, ql, qr));
    }
public:
    explicit SegmentTree(const std::vector<i64> &a) : n(int(a.size()) - 1), maximum(4 * a.size()), lazy(4 * a.size()) { build(1, 1, n, a); }
    void add(int l, int r, i64 delta) { add(1, 1, n, l, r, delta); }
    i64 query(int l, int r) { return query(1, 1, n, l, r); }
};
int main() {
    FastInput in; FastOutput out;
    int n, m; in >> n >> m;
    std::vector<i64> a(n + 1); for (int i = 1; i <= n; ++i) in >> a[i];
    SegmentTree tree(a);
    while (m--) {
        int type, l, r; in >> type >> l >> r;
        if (type == 0) { i64 k; in >> k; tree.add(l, r, k); }
        else out << tree.query(l, r) << '\n';
    }
}
