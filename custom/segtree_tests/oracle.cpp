// Independent references: Fenwick counts and square-root decomposition.
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class Fenwick {
    std::vector<int> bit;
public:
    explicit Fenwick(int n) : bit(n + 1) {}
    void add(int i, int x) {
        for (++i; i < int(bit.size()); i += i & -i) bit[i] += x;
    }
    int prefix(int r) const {
        int total = 0;
        for (; r > 0; r -= r & -r) total += bit[r];
        return total;
    }
    int range(int l, int r) const { return l > r ? 0 : prefix(r + 1) - prefix(l); }
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
    auto contribution = [&](int i) {
        if (kind == 10) return int(a[i]);
        if (kind == 50) return int(a[i] % 2 == 0);
        if (kind == 51) return int(a[i] == 0);
        if (kind == 90) return int(i > 0 && a[i] != a[i - 1]);
        return 0;
    };
    for (int i = 0; i < n; ++i) {
        first.add(i, contribution(i));
        second.add(i, a[i] < 0);
    }
    constexpr int B = 700;
    int blocks = (n + B - 1) / B;
    std::vector<long long> mn(blocks), mx(blocks);
    std::vector<int> count(blocks);
    auto rebuild = [&](int b) {
        mn[b] = std::numeric_limits<long long>::max();
        mx[b] = std::numeric_limits<long long>::lowest();
        count[b] = 0;
        for (int i = b * B; i < std::min(n, (b + 1) * B); ++i) {
            mn[b] = std::min(mn[b], a[i]);
            if (a[i] > mx[b]) { mx[b] = a[i]; count[b] = 1; }
            else if (a[i] == mx[b]) ++count[b];
        }
    };
    if (kind == 20 || kind == 60) for (int b = 0; b < blocks; ++b) rebuild(b);
    while (q--) {
        int type, l;
        std::cin >> type >> l;
        --l;
        if (type == 1) {
            long long x;
            if (kind == 10) x = 1 - a[l];
            else std::cin >> x;
            first.add(l, -contribution(l));
            if (kind == 90 && l + 1 < n) first.add(l + 1, -contribution(l + 1));
            second.add(l, -(a[l] < 0));
            a[l] = x;
            first.add(l, contribution(l));
            if (kind == 90 && l + 1 < n) first.add(l + 1, contribution(l + 1));
            second.add(l, a[l] < 0);
            if (kind == 20 || kind == 60) rebuild(l / B);
        } else {
            int r;
            std::cin >> r;
            --r;
            if (kind == 10) std::cout << first.range(l, r) << '\n';
            if (kind == 50) {
                int even = first.range(l, r);
                std::cout << even << ' ' << r - l + 1 - even << '\n';
            }
            if (kind == 51) std::cout << (first.range(l, r) ? '0' : second.range(l, r) % 2 ? '-' : '+') << '\n';
            if (kind == 90) std::cout << 1 + first.range(l + 1, r) << '\n';
            if (kind == 20 || kind == 60) {
                long long low = std::numeric_limits<long long>::max();
                long long high = std::numeric_limits<long long>::lowest();
                int occurrences = 0;
                auto consume = [&](long long small, long long large, int copies) {
                    low = std::min(low, small);
                    if (large > high) { high = large; occurrences = copies; }
                    else if (large == high) occurrences += copies;
                };
                while (l <= r) {
                    if (l % B == 0 && l + B - 1 <= r) {
                        consume(mn[l / B], mx[l / B], count[l / B]); l += B;
                    } else { consume(a[l], a[l], 1); ++l; }
                }
                if (kind == 20) std::cout << low << ' ' << high << ' ' << high - low << '\n';
                else std::cout << high << ' ' << occurrences << '\n';
            }
        }
    }
}
