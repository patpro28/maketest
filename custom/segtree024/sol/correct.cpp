#include <algorithm>
#include <cstdio>
#include <vector>

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
    int minimum = 1000000001;
    int maximum = -1000000001;
};

Node leaf(int value) { return {value, value}; }

Node merge(const Node &left, const Node &right) {
    return {std::min(left.minimum, right.minimum),
            std::max(left.maximum, right.maximum)};
}

class SegmentTree {
    int size = 1;
    std::vector<Node> nodes;

public:
    explicit SegmentTree(const std::vector<int> &values) {
        int n = static_cast<int>(values.size()) - 1;
        while (size < n) size *= 2;
        nodes.resize(2 * size, Node{});
        for (int i = 1; i <= n; ++i) nodes[size + i - 1] = leaf(values[i]);
        for (int v = size - 1; v > 0; --v) {
            nodes[v] = merge(nodes[2 * v], nodes[2 * v + 1]);
        }
    }

    void assign(int index, int value) {
        int v = size + index - 1;
        nodes[v] = leaf(value);
        for (v /= 2; v > 0; v /= 2) {
            nodes[v] = merge(nodes[2 * v], nodes[2 * v + 1]);
        }
    }

    Node query(int left, int right) const {
        Node result = Node{};
        // Convert to a half-open interval of leaf indices.
        for (left += size - 1, right += size; left < right; left /= 2, right /= 2) {
            if (left % 2) result = merge(result, nodes[left++]);
            if (right % 2) result = merge(result, nodes[--right]);
        }
        return result;
    }
};

int main() {
    FastInput in;
    FastOutput out;
    int n, q;
    in >> n >> q;
    std::vector<int> values(n + 1);
    for (int i = 1; i <= n; ++i) {
        in >> values[i];
    }
    SegmentTree tree(values);
    while (q--) {
        int type, l;
        in >> type >> l;
        if (type == 1) {
            int value;
            in >> value;
            tree.assign(l, value);
        } else {
            int r, reference;
            in >> r >> reference;
            Node result = tree.query(l, r);
            out << std::max(result.maximum - reference, reference - result.minimum) << '\n';
        }
    }
}
