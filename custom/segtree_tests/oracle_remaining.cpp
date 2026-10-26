// Independent references: Fenwick sums and square-root blocks.
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
    std::vector<long long> a(n);
    for (auto &x : a) std::cin >> x;
    Fenwick first(n), second(n);
    auto contribution = [&](long long x, int i) {
        if (kind == 12) return std::max(x, 0LL);
        if (kind == 13) return i % 2 ? -x : x;
        return 0LL;
    };
    for (int i = 0; i < n; ++i) {
        first.add(i, contribution(a[i], i));
        if (kind == 12) second.add(i, std::max(-a[i], 0LL));
    }
    constexpr int B = 500;
    const long long INF = std::numeric_limits<long long>::max();
    const long long NEG = std::numeric_limits<long long>::lowest();
    struct Block { long long mn, mx, top1, top2, difference; };
    std::vector<Block> blocks((n + B - 1) / B);
    auto insert = [](long long x, long long &top1, long long &top2) {
        if (x >= top1) { top2 = top1; top1 = x; }
        else if (x > top2) top2 = x;
    };
    auto rebuild = [&](int b) {
        Block &block = blocks[b];
        block = {INF, NEG, NEG, NEG, 0};
        for (int i = b * B; i < std::min(n, (b + 1) * B); ++i) {
            if (kind == 1 || kind == 23) {
                block.mn = std::min(block.mn, a[i]);
                block.mx = std::max(block.mx, a[i]);
            }
            if (kind == 22) insert(a[i], block.top1, block.top2);
            if (kind == 32) block.difference = std::gcd(block.difference, std::llabs(a[i] - a[b * B]));
        }
    };
    if (kind != 12 && kind != 13) for (int b = 0; b < int(blocks.size()); ++b) rebuild(b);
    while (q--) {
        int type = 2, l;
        if (kind == 1) std::cin >> l;
        else std::cin >> type >> l;
        --l;
        if (type == 1) {
            long long x;
            std::cin >> x;
            first.add(l, contribution(x, l) - contribution(a[l], l));
            if (kind == 12) second.add(l, std::max(-x, 0LL) - std::max(-a[l], 0LL));
            a[l] = x;
            if (kind != 12 && kind != 13) rebuild(l / B);
            continue;
        }
        int r;
        std::cin >> r;
        --r;
        if (kind == 12) { std::cout << first.range(l, r) << ' ' << second.range(l, r) << '\n'; continue; }
        if (kind == 13) { std::cout << (l % 2 ? -1 : 1) * first.range(l, r) << '\n'; continue; }
        long long u = 0, v = 0;
        if (kind == 23) std::cin >> u >> v;
        long long mn = INF, mx = NEG, top1 = NEG, top2 = NEG, g = 0;
        long long anchor = a[l];
        while (l <= r) {
            if (l % B == 0 && l + B - 1 <= r) {
                const Block &block = blocks[l / B];
                if (kind == 1 || kind == 23) { mn = std::min(mn, block.mn); mx = std::max(mx, block.mx); }
                if (kind == 22) { insert(block.top1, top1, top2); insert(block.top2, top1, top2); }
                if (kind == 32) g = std::gcd(std::gcd(g, block.difference), std::llabs(a[l] - anchor));
                l += B;
            } else {
                if (kind == 1 || kind == 23) { mn = std::min(mn, a[l]); mx = std::max(mx, a[l]); }
                if (kind == 22) insert(a[l], top1, top2);
                if (kind == 32) g = std::gcd(g, std::llabs(a[l] - anchor));
                ++l;
            }
        }
        if (kind == 1) std::cout << mn << ' ' << mx << ' ' << mx - mn << '\n';
        if (kind == 22) std::cout << top1 + top2 << '\n';
        if (kind == 23) std::cout << (mn >= u && mx <= v ? "YES" : "NO") << '\n';
        if (kind == 32) std::cout << g << '\n';
    }
}
