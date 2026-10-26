// Independent references: prefix XOR, prefix-balance RMQ, Fenwick and square-root blocks.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
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
    std::cin >> n >> q;
    if (kind == 4) {
        std::string s;
        std::cin >> s;
        std::vector<int> prefix(n + 1), logs(n + 2);
        for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + (s[i] == '(' ? 1 : -1);
        for (int i = 2; i <= n + 1; ++i) logs[i] = logs[i / 2] + 1;
        std::vector<std::vector<int>> table(logs[n + 1] + 1, std::vector<int>(n + 1));
        table[0] = prefix;
        for (int k = 1; k <= logs[n + 1]; ++k)
            for (int i = 0; i + (1 << k) <= n + 1; ++i)
                table[k][i] = std::min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        while (q--) {
            int l, r;
            std::cin >> l >> r;
            int k = logs[r - l + 1];
            int low = std::min(table[k][l], table[k][r - (1 << k) + 1]);
            std::cout << (prefix[r] == prefix[l - 1] && low >= prefix[l - 1] ? "YES" : "NO") << '\n';
        }
        return 0;
    }
    std::vector<long long> a(n);
    for (auto &x : a) std::cin >> x;
    if (kind == 3) {
        std::vector<long long> prefix(n + 1);
        for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] ^ a[i];
        while (q--) { int l, r; std::cin >> l >> r; std::cout << (prefix[r] ^ prefix[l - 1]) << '\n'; }
        return 0;
    }
    Fenwick sum(n), auxiliary(n);
    for (int i = 0; i < n; ++i) {
        sum.add(i, a[i]);
        if (kind == 14) auxiliary.add(i, (i + 1LL) * a[i]);
        if (kind == 15) auxiliary.add(i, a[i] * a[i]);
    }
    constexpr int B = 500;
    const long long INF = std::numeric_limits<long long>::max();
    const long long NEG = std::numeric_limits<long long>::lowest();
    struct Block { long long gcd = 0, mn = INF, mx = NEG, best = NEG; };
    std::vector<Block> blocks((n + B - 1) / B);
    std::vector<long long> differences(n);
    if (kind == 34) for (int i = 1; i < n; ++i) differences[i] = std::llabs(a[i] - a[i - 1]);
    auto rebuild = [&](int b) {
        Block block;
        for (int i = b * B; i < std::min(n, (b + 1) * B); ++i) {
            if (kind == 25) {
                if (block.mn != INF) block.best = std::max(block.best, a[i] - block.mn);
                block.mn = std::min(block.mn, a[i]);
                block.mx = std::max(block.mx, a[i]);
            }
            if (kind == 33) block.gcd = std::gcd(block.gcd, a[i]);
            if (kind == 34) block.gcd = std::gcd(block.gcd, differences[i]);
        }
        blocks[b] = block;
    };
    if (kind == 25 || kind == 33 || kind == 34) for (int b = 0; b < int(blocks.size()); ++b) rebuild(b);
    auto range_gcd = [&](int l, int r) {
        long long result = 0;
        while (l <= r) {
            if (l % B == 0 && l + B - 1 <= r) { result = std::gcd(result, blocks[l / B].gcd); l += B; }
            else { result = std::gcd(result, kind == 34 ? differences[l] : a[l]); ++l; }
        }
        return result;
    };
    while (q--) {
        int type, l;
        std::cin >> type >> l;
        --l;
        if (type == 1) {
            long long x;
            std::cin >> x;
            sum.add(l, x - a[l]);
            if (kind == 14) auxiliary.add(l, (l + 1LL) * (x - a[l]));
            if (kind == 15) auxiliary.add(l, x * x - a[l] * a[l]);
            a[l] = x;
            if (kind == 25 || kind == 33) rebuild(l / B);
            if (kind == 34) {
                if (l > 0) differences[l] = std::llabs(a[l] - a[l - 1]);
                if (l + 1 < n) differences[l + 1] = std::llabs(a[l + 1] - a[l]);
                rebuild(l / B);
                if (l + 1 < n && (l + 1) / B != l / B) rebuild((l + 1) / B);
            }
            continue;
        }
        int r;
        std::cin >> r;
        --r;
        if (kind == 14) std::cout << auxiliary.range(l, r) - l * sum.range(l, r) << '\n';
        if (kind == 15) {
            long long c;
            std::cin >> c;
            std::cout << auxiliary.range(l, r) - 2 * c * sum.range(l, r) + (r - l + 1LL) * c * c << '\n';
        }
        if (kind == 33) {
            long long g = range_gcd(l, r);
            std::cout << g << ' ' << sum.range(l, r) / g << '\n';
        }
        if (kind == 34) {
            long long c;
            std::cin >> c;
            std::cout << std::gcd(range_gcd(l + 1, r), std::llabs(a[l] - c)) << '\n';
        }
        if (kind == 25) {
            long long lowest = INF, best = NEG;
            while (l <= r) {
                if (l % B == 0 && l + B - 1 <= r) {
                    const Block &b = blocks[l / B];
                    if (lowest != INF) best = std::max(best, b.mx - lowest);
                    best = std::max(best, b.best);
                    lowest = std::min(lowest, b.mn);
                    l += B;
                } else {
                    if (lowest != INF) best = std::max(best, a[l] - lowest);
                    lowest = std::min(lowest, a[l]);
                    ++l;
                }
            }
            std::cout << best << '\n';
        }
    }
}
