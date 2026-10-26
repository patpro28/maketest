// Independent references: ordered sets, Fenwick binary lifting and square-root blocks.
#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

class Fenwick {
    int n;
    std::vector<long long> bit;
public:
    explicit Fenwick(int size) : n(size), bit(size + 1) {}
    void add(int i, long long x) { for (++i; i <= n; i += i & -i) bit[i] += x; }
    long long prefix(int r) const {
        long long result = 0;
        for (; r > 0; r -= r & -r) result += bit[r];
        return result;
    }
    int last_prefix_at_most(long long limit) const {
        int pos = 0, step = 1;
        long long total = 0;
        while (step * 2 <= n) step *= 2;
        for (; step; step /= 2) {
            int next = pos + step;
            if (next <= n && total + bit[next] <= limit) { pos = next; total += bit[next]; }
        }
        return pos;
    }
    int first_prefix_at_least(long long target) const {
        return prefix(n) < target ? -1 : last_prefix_at_most(target - 1) + 1;
    }
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
    std::set<int> empty, boundaries;
    Fenwick sum(n), count(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) empty.insert(i);
        if (i && a[i] != a[i - 1]) boundaries.insert(i);
        sum.add(i, a[i]); count.add(i, a[i] > 0);
    }
    constexpr int B = 500;
    struct Block { long long sum = 0, mn, mx; };
    std::vector<Block> blocks((n + B - 1) / B);
    auto rebuild = [&](int b) {
        Block value;
        value.mn = std::numeric_limits<long long>::max();
        value.mx = std::numeric_limits<long long>::lowest();
        for (int i = b * B; i < std::min(n, (b + 1) * B); ++i) {
            value.sum += a[i]; value.mn = std::min(value.mn, a[i]); value.mx = std::max(value.mx, a[i]);
        }
        blocks[b] = value;
    };
    bool needs_blocks = kind == 140 || kind == 150 || kind == 160 || kind == 180 || kind == 190;
    if (needs_blocks) for (int b = 0; b < int(blocks.size()); ++b) rebuild(b);
    auto set_value = [&](int i, long long x) {
        sum.add(i, x - a[i]); count.add(i, int(x > 0) - int(a[i] > 0));
        if (x == 0) empty.insert(i); else empty.erase(i);
        a[i] = x;
        if (i > 0) { if (a[i] == a[i - 1]) boundaries.erase(i); else boundaries.insert(i); }
        if (i + 1 < n) { if (a[i + 1] == a[i]) boundaries.erase(i + 1); else boundaries.insert(i + 1); }
        if (needs_blocks) rebuild(i / B);
    };
    auto first = [&](int l, int r, int mode, long long x, long long y) {
        while (l <= r) {
            if (l % B == 0 && l + B - 1 <= r) {
                const Block &b = blocks[l / B];
                bool absent = mode == 0 ? b.mx < x : mode == 1 ? b.mn > x : b.mn >= x && b.mx <= y;
                if (absent) { l += B; continue; }
            }
            bool match = mode == 0 ? a[l] >= x : mode == 1 ? a[l] <= x : a[l] < x || a[l] > y;
            if (match) return l + 1;
            ++l;
        }
        return -1;
    };
    while (q--) {
        if (kind == 140) {
            long long x; std::cin >> x;
            int answer = first(0, n - 1, 0, x, 0);
            std::cout << answer << '\n';
            if (answer != -1) set_value(answer - 1, a[answer - 1] - x);
            continue;
        }
        int type;
        std::cin >> type;
        if (type == 1) {
            int i; std::cin >> i; --i;
            long long x;
            if (kind == 100 || kind == 120) x = 1 - a[i];
            else std::cin >> x;
            set_value(i, x);
            continue;
        }
        if (kind == 100) std::cout << (empty.empty() ? -1 : *empty.begin() + 1) << '\n';
        if (kind == 110) {
            long long c; std::cin >> c;
            int left = a[0] != c ? 1 : boundaries.empty() ? -1 : *boundaries.begin() + 1;
            int right = a[n - 1] != c ? n : boundaries.empty() ? -1 : *boundaries.rbegin();
            std::cout << left << ' ' << right << '\n';
        }
        if (kind == 120) { long long k; std::cin >> k; std::cout << count.first_prefix_at_least(k) << '\n'; }
        if (kind == 130) { long long target; std::cin >> target; std::cout << sum.first_prefix_at_least(target) << '\n'; }
        if (kind == 150) { long long x; std::cin >> x; std::cout << first(0, n - 1, 1, x, 0) << '\n'; }
        if (kind == 160) {
            int l, r; long long low, high; std::cin >> l >> r >> low >> high;
            std::cout << first(l - 1, r - 1, 2, low, high) << '\n';
        }
        if (kind == 170) {
            int l; long long budget; std::cin >> l >> budget;
            std::cout << sum.last_prefix_at_most(sum.prefix(l - 1) + budget) << '\n';
        }
        if (kind == 180) {
            int l; long long budget, difference; std::cin >> l >> budget >> difference; --l;
            long long total = 0, mn = std::numeric_limits<long long>::max(), mx = std::numeric_limits<long long>::lowest();
            while (l < n) {
                if (l % B == 0 && l + B <= n) {
                    const Block &b = blocks[l / B];
                    long long small = std::min(mn, b.mn), large = std::max(mx, b.mx);
                    if (total + b.sum <= budget && large - small <= difference) {
                        total += b.sum; mn = small; mx = large; l += B; continue;
                    }
                }
                long long small = std::min(mn, a[l]), large = std::max(mx, a[l]);
                if (total + a[l] > budget || large - small > difference) break;
                total += a[l]; mn = small; mx = large; ++l;
            }
            std::cout << l << '\n';
        }
        if (kind == 190) {
            long long x; std::cin >> x;
            if (type == 2) std::cout << first(0, n - 1, 0, x, 0) << '\n';
            if (type == 3) std::cout << sum.first_prefix_at_least(x) << '\n';
            if (type == 4) std::cout << count.first_prefix_at_least(x) << '\n';
        }
    }
}
