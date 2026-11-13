#include <algorithm>
#include <cstdio>
#include <vector>

using i64 = long long;

class FastInput {
    char data[1 << 16];
    int pos = 0, size = 0;
    char get() {
        if (pos == size) { size = int(std::fread(data, 1, sizeof(data), stdin)); pos = 0; }
        return pos < size ? data[pos++] : 0;
    }
public:
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
    i64 maximum;
    int count;
};

Node leaf(i64 value, int) {
    return {value, 1};
}

Node merge(const Node &left, const Node &right) {
    if (left.maximum != right.maximum) {
        return left.maximum > right.maximum ? left : right;
    }
    return {left.maximum, left.count + right.count};
}

void shift(Node &node, i64 delta) {
    node.maximum += delta;
}

class SegmentTree {
    int n;
    std::vector<Node> nodes;
    std::vector<i64> lazy;

    void build(int vertex, int left, int right, const std::vector<i64> &values) {
        if (left == right) {
            nodes[vertex] = leaf(values[left], left);
            return;
        }
        int middle = (left + right) / 2;
        build(2 * vertex, left, middle, values);
        build(2 * vertex + 1, middle + 1, right, values);
        nodes[vertex] = merge(nodes[2 * vertex], nodes[2 * vertex + 1]);
    }

    void apply(int vertex, i64 delta) {
        shift(nodes[vertex], delta);
        lazy[vertex] += delta;
    }

    void push(int vertex) {
        if (lazy[vertex] == 0) return;
        apply(2 * vertex, lazy[vertex]);
        apply(2 * vertex + 1, lazy[vertex]);
        lazy[vertex] = 0;
    }

    void add(int vertex, int left, int right, int first, int last, i64 delta) {
        if (first <= left && right <= last) {
            apply(vertex, delta);
            return;
        }
        push(vertex);
        int middle = (left + right) / 2;
        if (first <= middle) add(2 * vertex, left, middle, first, last, delta);
        if (last > middle) add(2 * vertex + 1, middle + 1, right, first, last, delta);
        nodes[vertex] = merge(nodes[2 * vertex], nodes[2 * vertex + 1]);
    }

    Node query(int vertex, int left, int right, int first, int last) {
        if (first <= left && right <= last) return nodes[vertex];
        push(vertex);
        int middle = (left + right) / 2;
        if (last <= middle) return query(2 * vertex, left, middle, first, last);
        if (first > middle) return query(2 * vertex + 1, middle + 1, right, first, last);
        return merge(query(2 * vertex, left, middle, first, last),
                     query(2 * vertex + 1, middle + 1, right, first, last));
    }

public:
    explicit SegmentTree(const std::vector<i64> &values)
        : n(static_cast<int>(values.size()) - 1),
          nodes(4 * values.size()), lazy(4 * values.size()) {
        build(1, 1, n, values);
    }

    void add(int first, int last, i64 delta) {
        add(1, 1, n, first, last, delta);
    }

    Node query(int first, int last) {
        return query(1, 1, n, first, last);
    }
};

int main() {
    FastInput in;
    FastOutput out;
    int n, q;
    in >> n >> q;
    std::vector<i64> values(n + 1);
    for (int i = 1; i <= n; ++i) in >> values[i];
    SegmentTree tree(values);
    while (q--) {
        int type, left, right;
        in >> type >> left >> right;
        if (type == 0) {
            i64 delta;
            in >> delta;
            tree.add(left, right, delta);
        } else {
            Node result = tree.query(left, right);
            out << result.maximum << ' ' << result.count << '\n';
        }
    }
}
