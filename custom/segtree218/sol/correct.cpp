#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>
#include <utility>
using i64 = long long;
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

using Total = i64;

class SegmentTree {
    int size;
    const std::vector<i64> &weightPrefix;
    std::vector<Total> values;
    std::vector<i64> pending;

    i64 weight(int left, int right) const {
        return weightPrefix[right] - weightPrefix[left - 1];
    }

    void pull(int node) {
        values[node] = values[node * 2] + values[node * 2 + 1];
    }

    void build(int node, int left, int right, const std::vector<i64> &a) {
        if (left == right) {
            values[node] = a[left] * weight(left, left);
            return;
        }
        int mid = (left + right) / 2;
        build(node * 2, left, mid, a);
        build(node * 2 + 1, mid + 1, right, a);
        pull(node);
    }

    void apply(int node, int left, int right, i64 delta) {
        values[node] += delta * weight(left, right);
        pending[node] += delta;
    }

    void push(int node, int left, int mid, int right) {
        if (pending[node] == 0) return;
        apply(node * 2, left, mid, pending[node]);
        apply(node * 2 + 1, mid + 1, right, pending[node]);
        pending[node] = 0;
    }

    void add(int node, int left, int right, int from, int to, i64 delta) {
        if (from <= left && right <= to) {
            apply(node, left, right, delta);
            return;
        }
        int mid = (left + right) / 2;
        push(node, left, mid, right);
        if (from <= mid) add(node * 2, left, mid, from, to, delta);
        if (to > mid) add(node * 2 + 1, mid + 1, right, from, to, delta);
        pull(node);
    }

    Total query(int node, int left, int right, int from, int to) {
        if (from <= left && right <= to) return values[node];
        int mid = (left + right) / 2;
        push(node, left, mid, right);
        Total answer{};
        if (from <= mid) answer = query(node * 2, left, mid, from, to);
        if (to > mid) answer = answer + query(node * 2 + 1, mid + 1, right, from, to);
        return answer;
    }

public:
    explicit SegmentTree(const std::vector<i64> &a, const std::vector<i64> &prefix)
        : size(int(a.size()) - 1), weightPrefix(prefix), values(4 * a.size()), pending(4 * a.size()) {
        build(1, 1, size, a);
    }

    void add(int left, int right, i64 delta) { add(1, 1, size, left, right, delta); }
    Total query(int left, int right) { return query(1, 1, size, left, right); }
};

struct Operation {
    int type, left, right;
    i64 delta = 0;
};

int main() {
    FastInput in;
    FastOutput out;
    int q;
    in >> q;
    std::vector<Operation> operations(q);
    std::vector<int> points;
    points.reserve(2 * q);
    for (Operation &op : operations) {
        in >> op.type >> op.left >> op.right;
        if (op.type == 1) in >> op.delta;
        points.push_back(op.left);
        points.push_back(op.right + 1);
    }
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    // Leaf i represents [points[i-1], points[i]).
    std::vector<i64> weightPrefix(points.size());
    for (size_t i = 1; i < points.size(); ++i) weightPrefix[i] = points[i] - points[0];
    SegmentTree tree(std::vector<i64>(points.size()), weightPrefix);
    for (const Operation &op : operations) {
        int left = int(std::lower_bound(points.begin(), points.end(), op.left) - points.begin()) + 1;
        int right = int(std::lower_bound(points.begin(), points.end(), op.right + 1) - points.begin());
        if (op.type == 1) tree.add(left, right, op.delta);
        else out << tree.query(left, right) << '\n';
    }
}
