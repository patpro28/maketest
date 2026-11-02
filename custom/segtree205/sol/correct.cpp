#include <algorithm>
#include <array>
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




struct Tag { std::array<int, 3> image = {0, 1, 2}; };
const Tag IDENTITY;
bool neutral(const Tag &t) { return t.image == IDENTITY.image; }
Tag compose(const Tag &older, const Tag &newer) {
    Tag result;
    for (int c = 0; c < 3; ++c) result.image[c] = newer.image[older.image[c]];
    return result;
}
i64 transform(i64 value, const Tag &t) { return t.image[int(value) - 1] + 1; }

class SegmentTree {
    int n;
    std::vector<i64> initial;
    std::vector<Tag> lazy;
    void apply(int v, const Tag &tag) { lazy[v] = compose(lazy[v], tag); }
    void push(int v) {
        if (neutral(lazy[v])) return;
        apply(v * 2, lazy[v]); apply(v * 2 + 1, lazy[v]); lazy[v] = IDENTITY;
    }
    void update(int v, int l, int r, int ql, int qr, const Tag &tag) {
        if (ql <= l && r <= qr) { apply(v, tag); return; }
        push(v);
        int mid = (l + r) / 2;
        if (ql <= mid) update(v * 2, l, mid, ql, qr, tag);
        if (qr > mid) update(v * 2 + 1, mid + 1, r, ql, qr, tag);
    }
    i64 get(int v, int l, int r, int pos) {
        if (l == r) return transform(initial[pos], lazy[v]);
        push(v);
        int mid = (l + r) / 2;
        return pos <= mid ? get(v * 2, l, mid, pos) : get(v * 2 + 1, mid + 1, r, pos);
    }
public:
    explicit SegmentTree(const std::vector<i64> &a) : n(int(a.size()) - 1), initial(a), lazy(4 * a.size(), IDENTITY) {}
    void update(int l, int r, const Tag &tag) { update(1, 1, n, l, r, tag); }
    i64 get(int pos) { return get(1, 1, n, pos); }
};
int main() {
    FastInput in; FastOutput out;
    int n, q; in >> n >> q;
    std::vector<i64> a(n + 1); for (int i = 1; i <= n; ++i) in >> a[i];
    SegmentTree tree(a);
    while (q--) {
        int type, l; in >> type >> l;
        if (type == 1) {
            int r; in >> r;
            int x, y; in >> x >> y; Tag tag;
            std::swap(tag.image[x - 1], tag.image[y - 1]); tree.update(l, r, tag);
        } else out << tree.get(l) << '\n';
    }
}
