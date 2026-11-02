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
    int size = 1;
    std::vector<i64> tree;
public:
    explicit SegmentTree(const std::vector<i64> &a) {
        while (size < int(a.size()) - 1) size *= 2;
        tree.assign(size * 2, 0);
        for (int i = 1; i < int(a.size()); ++i) tree[size + i - 1] = a[i];
        for (int v = size - 1; v; --v) tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
    void update(int pos, i64 value) {
        int v = size + pos - 1; tree[v] = value;
        while ((v /= 2)) tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
    i64 total() const { return tree[1]; }
    std::pair<int, i64> locate(i64 rank) const {
        int v = 1;
        while (v < size) {
            if (tree[v * 2] >= rank) v *= 2;
            else { rank -= tree[v * 2]; v = v * 2 + 1; }
        }
        return {v - size + 1, rank};
    }
};

int main() {
    FastInput in; FastOutput out;
    int n, q; in >> n >> q;
    std::vector<i64> occupied(n + q + 1);
    std::vector<int> position(n + 1), owner(n + q + 1);
    for (int i = 1; i <= n; ++i) { occupied[i] = 1; position[i] = i; owner[i] = i; }
    SegmentTree tree(occupied);
    int tail = n;
    while (q--) {
        int type, x; in >> type >> x;
        if (type == 1) {
            tree.update(position[x], 0);
            position[x] = ++tail; owner[tail] = x; tree.update(tail, 1);
        } else out << owner[tree.locate(x).first] << '\n';
    }
}
