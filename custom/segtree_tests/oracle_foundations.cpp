// Independent references using prefix sums, Fenwick trees and square-root blocks.
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <utility>
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
    long long k = 0;
    std::cin >> n >> q;
    if (kind == 2) std::cin >> k;
    std::vector<long long> a(n);
    for (auto &x : a) std::cin >> x;
    if (kind == 0 || kind == 2) {
        std::vector<long long> prefix(n + 1);
        for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + (kind == 0 ? a[i] : int(a[i] >= k));
        while (q--) {
            int l, r;
            std::cin >> l >> r;
            std::cout << prefix[r] - prefix[l - 1] << '\n';
        }
        return 0;
    }
    Fenwick sum(n);
    const std::array<int, 7> powers = {2, 4, 8, 3, 9, 5, 7};
    std::vector<Fenwick> divisible(7, Fenwick(n));
    for (int i = 0; i < n; ++i) {
        if (kind == 11) sum.add(i, a[i]);
        if (kind == 31) for (int j = 0; j < 7; ++j) divisible[j].add(i, a[i] % powers[j] == 0);
    }
    constexpr int B = 500;
    int blocks = (n + B - 1) / B;
    using Entry = std::pair<long long, int>;
    std::vector<Entry> minimum(blocks);
    std::vector<long long> gcd(blocks);
    auto rebuild = [&](int b) {
        minimum[b] = {std::numeric_limits<long long>::max(), n};
        gcd[b] = 0;
        for (int i = b * B; i < std::min(n, (b + 1) * B); ++i) {
            if (kind == 21) minimum[b] = std::min(minimum[b], Entry{a[i], i});
            if (kind == 30) gcd[b] = std::gcd(gcd[b], a[i]);
        }
    };
    if (kind == 21 || kind == 30) for (int b = 0; b < blocks; ++b) rebuild(b);
    while (q--) {
        int type, l;
        std::cin >> type >> l;
        --l;
        if (type == 1) {
            long long x;
            std::cin >> x;
            if (kind == 11) sum.add(l, x - a[l]);
            if (kind == 31) for (int j = 0; j < 7; ++j)
                divisible[j].add(l, int(x % powers[j] == 0) - int(a[l] % powers[j] == 0));
            a[l] = x;
            if (kind == 21 || kind == 30) rebuild(l / B);
        } else {
            int r;
            std::cin >> r;
            --r;
            if (kind == 11) std::cout << sum.range(l, r) << '\n';
            if (kind == 31) {
                int two = 1, three = 1, five = 1, seven = 1;
                for (int j = 0; j < 3; ++j) if (divisible[j].range(l, r)) two = powers[j];
                for (int j = 3; j < 5; ++j) if (divisible[j].range(l, r)) three = powers[j];
                if (divisible[5].range(l, r)) five = 5;
                if (divisible[6].range(l, r)) seven = 7;
                std::cout << two * three * five * seven << '\n';
            }
            if (kind == 21 || kind == 30) {
                Entry best = {std::numeric_limits<long long>::max(), n};
                long long g = 0;
                while (l <= r) {
                    if (l % B == 0 && l + B - 1 <= r) {
                        if (kind == 21) best = std::min(best, minimum[l / B]);
                        else g = std::gcd(g, gcd[l / B]);
                        l += B;
                    } else {
                        if (kind == 21) best = std::min(best, Entry{a[l], l});
                        else g = std::gcd(g, a[l]);
                        ++l;
                    }
                }
                if (kind == 21) std::cout << best.first << ' ' << best.second + 1 << '\n';
                else std::cout << g << '\n';
            }
        }
    }
}
