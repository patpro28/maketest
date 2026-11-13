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

class SegmentTree {
    int size = 1;
    std::vector<i64> sums;

public:
    explicit SegmentTree(const std::vector<i64> &a) {
        int n = int(a.size()) - 1;
        while (size < n) size *= 2;
        sums.resize(2 * size);
        for (int i = 1; i <= n; ++i) sums[size + i - 1] = a[i];
        for (int node = size - 1; node > 0; --node) {
            sums[node] = sums[node * 2] + sums[node * 2 + 1];
        }
    }

    void add(int position, i64 value) {
        int node = size + position - 1;
        sums[node] += value;
        for (node /= 2; node > 0; node /= 2) {
            sums[node] = sums[node * 2] + sums[node * 2 + 1];
        }
    }

    i64 query(int left, int right) const {
        i64 result = 0;
        // Convert to a half-open interval of leaf indices.
        for (left += size - 1, right += size; left < right; left /= 2, right /= 2) {
            if (left % 2) result += sums[left++];
            if (right % 2) result += sums[--right];
        }
        return result;
    }
};

int main() {
    FastInput in;
    FastOutput out;
    int n, q;
    in >> n >> q;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) in >> a[i];
    SegmentTree tree(a);
    while (q--) {
        int type, left;
        in >> type >> left;
        if (type == 1) {
            i64 amount;
            in >> amount;
            tree.add(left, amount);
        } else {
            int right;
            in >> right;
            i64 answer = left <= right ? tree.query(left, right)
                                       : tree.query(left, n) + tree.query(1, right);
            out << answer << '\n';
        }
    }
}
