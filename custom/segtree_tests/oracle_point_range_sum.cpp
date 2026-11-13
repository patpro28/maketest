#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

class Fenwick {
    std::vector<i64> tree;

    i64 prefix(int index) const {
        i64 sum = 0;
        for (; index > 0; index -= index & -index) sum += tree[index];
        return sum;
    }

public:
    explicit Fenwick(int n) : tree(n + 1) {}

    void add(int index, i64 delta) {
        for (int n = static_cast<int>(tree.size()); index < n; index += index & -index) {
            tree[index] += delta;
        }
    }

    i64 range(int left, int right) const {
        return prefix(right) - prefix(left - 1);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    int kind = std::atoi(argv[1]);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, step = 1;
    std::cin >> n >> q;
    if (kind == 18) std::cin >> step;
    std::vector<i64> values(n + 1), weights(n + 1, 1);
    for (int i = 1; i <= n; ++i) std::cin >> values[i];
    if (kind == 19) {
        for (int i = 1; i <= n; ++i) std::cin >> weights[i];
    }
    std::vector<int> index(n + 1);
    if (kind == 18) {
        int next = 1;
        for (int first = 1; first <= step; ++first) {
            for (int i = first; i <= n; i += step) index[i] = next++;
        }
    } else {
        std::iota(index.begin(), index.end(), 0);
    }
    Fenwick sums(n);
    for (int i = 1; i <= n; ++i) sums.add(index[i], values[i] * weights[i]);

    for (int op = 0; op < q; ++op) {
        int type, left;
        std::cin >> type >> left;
        if (type == 1 && kind == 16) {
            int destination;
            i64 amount;
            std::cin >> destination >> amount;
            if (left == destination) continue;
            sums.add(left, -amount);
            sums.add(destination, amount);
        } else if (type == 1) {
            i64 value;
            std::cin >> value;
            if (kind == 17) {
                sums.add(left, value);
            } else {
                sums.add(index[left], (value - values[left]) * weights[left]);
                values[left] = value;
            }
        } else {
            int right;
            std::cin >> right;
            if (kind == 17 && left > right) {
                std::cout << sums.range(left, n) + sums.range(1, right) << '\n';
            } else {
                int last = right - (right - left) % step;
                std::cout << sums.range(index[left], index[last]) << '\n';
            }
        }
    }
}
