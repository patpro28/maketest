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
    i64 sum = 0;
    int maximum = 0, odd = 0;
};
Node leaf(int x) { return {x, x, x & 1}; }
Node merge(Node a, Node b) {
    return {a.sum + b.sum, std::max(a.maximum, b.maximum), a.odd + b.odd};
}
class SegmentTree {
    int size = 1;
    std::vector<Node> tree;
public:
    explicit SegmentTree(const std::vector<int> &a) {
        while (size < int(a.size())) size *= 2;
        tree.resize(size * 2);
        for (int i = 0; i < int(a.size()); ++i) tree[size + i] = leaf(a[i]);
        for (int v = size - 1; v; --v) tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    void update(int pos, int value) {
        int v = size + pos; tree[v] = leaf(value);
        while ((v /= 2)) tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    Node query(int l, int r) const {
        Node result;
        for (l += size, r += size; l < r; l /= 2, r /= 2) {
            if (l & 1) result = merge(result, tree[l++]);
            if (r & 1) result = merge(result, tree[--r]);
        }
        return result;
    }
};
int main() {
    FastInput in; FastOutput out;
    int n, q; in >> n >> q;
    std::vector<int> a(n); for (int &x : a) in >> x;
    SegmentTree tree(a);
    while (q--) {
        int type, x, y; in >> type >> x >> y;
        if (type == 1) tree.update(x - 1, y);
        else {
            Node result = tree.query(x - 1, y);
            int length = y - x + 1;
            int opposite = result.maximum & 1 ? length - result.odd : result.odd;
            out << (i64(length) * result.maximum - result.sum + opposite) / 2 << '\n';
        }
    }
}
