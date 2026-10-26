// Independent references: sparse GCD, Fenwick sums/counts, and square-root blocks.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Fenwick {
    std::vector<long long> bit;
public:
    explicit Fenwick(int n) : bit(n + 1) {}
    void add(int i, long long x) {
        for (++i; i < int(bit.size()); i += i & -i) bit[i] += x;
    }
    long long prefix(int r) const {
        long long result = 0;
        for (; r > 0; r -= r & -r) result += bit[r];
        return result;
    }
    long long range(int l, int r) const { return prefix(r + 1) - prefix(l); }
};

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    int kind = std::stoi(argv[1]);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    long long setting = 0;
    std::cin >> n >> q;
    if (kind == 15 || kind == 33 || kind == 51) std::cin >> setting;
    std::vector<long long> a(n);
    for (auto &x : a) std::cin >> x;
    if (kind == 4) {
        std::vector<int> logs(n + 1);
        for (int i = 2; i <= n; ++i) logs[i] = logs[i / 2] + 1;
        std::vector<std::vector<long long>> table(logs[n] + 1, std::vector<long long>(n));
        table[0] = a;
        for (int k = 1; k <= logs[n]; ++k)
            for (int i = 0; i + (1 << k) <= n; ++i)
                table[k][i] = std::gcd(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        while (q--) {
            int l, r;
            std::cin >> l >> r;
            --l; --r;
            int k = logs[r - l + 1];
            std::cout << std::gcd(table[k][l], table[k][r - (1 << k) + 1]) << '\n';
        }
        return 0;
    }
    Fenwick bit(n);
    for (int i = 0; i < n; ++i) bit.add(i, kind == 51 ? int(a[i] % setting == 0) : a[i]);
    constexpr int B = 500;
    struct Block { long long maximum = 0, first = 0, last = 0, lcm = 1; };
    std::vector<Block> blocks((n + B - 1) / B);
    auto combine = [&](long long x, long long y) {
        if (x > setting || y > setting) return setting + 1;
        __int128 product = static_cast<__int128>(x / std::gcd(x, y)) * y;
        return product > setting ? setting + 1 : static_cast<long long>(product);
    };
    auto rebuild = [&](int b) {
        int l = b * B, r = std::min(n, (b + 1) * B);
        Block value;
        value.first = a[l]; value.last = a[r - 1];
        for (int i = l; i < r; ++i) {
            if (kind == 25 && i > l) value.maximum = std::max(value.maximum, std::llabs(a[i] - a[i - 1]));
            if (kind == 33) value.lcm = combine(value.lcm, a[i]);
        }
        blocks[b] = value;
    };
    if (kind == 25 || kind == 33) for (int b = 0; b < int(blocks.size()); ++b) rebuild(b);
    while (q--) {
        int type, l;
        std::cin >> type >> l;
        --l;
        if (type == 1) {
            long long x;
            std::cin >> x;
            if (kind == 14) { a[l] += x; bit.add(l, x); }
            else {
                if (kind == 15) bit.add(l, x - a[l]);
                if (kind == 51) bit.add(l, int(x % setting == 0) - int(a[l] % setting == 0));
                a[l] = x;
                if (kind == 25 || kind == 33) rebuild(l / B);
            }
            continue;
        }
        int r;
        std::cin >> r;
        --r;
        if (kind == 14 || kind == 51) std::cout << bit.range(l, r) << '\n';
        if (kind == 15) std::cout << bit.range(l, r) % setting << '\n';
        if (kind == 33) {
            long long answer = 1;
            while (l <= r) {
                if (l % B == 0 && l + B - 1 <= r) { answer = combine(answer, blocks[l / B].lcm); l += B; }
                else { answer = combine(answer, a[l]); ++l; }
            }
            std::cout << (answer <= setting ? answer : -1) << '\n';
        }
        if (kind == 25) {
            long long answer = 0, previous = 0;
            bool has_previous = false;
            while (l <= r) {
                if (l % B == 0 && l + B - 1 <= r) {
                    const Block &b = blocks[l / B];
                    if (has_previous) answer = std::max(answer, std::llabs(b.first - previous));
                    answer = std::max(answer, b.maximum);
                    previous = b.last; has_previous = true; l += B;
                } else {
                    if (has_previous) answer = std::max(answer, std::llabs(a[l] - previous));
                    previous = a[l]; has_previous = true; ++l;
                }
            }
            std::cout << answer << '\n';
        }
    }
}
