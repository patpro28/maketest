// Independent references: ordered sets, a multiset, Fenwick trees and square-root blocks.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using i64 = long long;
constexpr i64 CAP = 1000000000000000001LL;
i64 capped(i64 a, i64 b) {
    if (a == CAP || b == CAP) return CAP;
    __int128 product = static_cast<__int128>(a / std::gcd(a, b)) * b;
    return product >= CAP ? CAP : static_cast<i64>(product);
}
struct Fenwick {
    int n; std::vector<i64> f;
    explicit Fenwick(int size) : n(size), f(size + 1) {}
    void add(int i, i64 x) { for (; i <= n; i += i & -i) f[i] += x; }
    i64 sum(int i) const { i64 result = 0; for (; i; i -= i & -i) result += f[i]; return result; }
    int select(i64 target) const {
        int p = 0, step = 1; while (step <= n / 2) step *= 2;
        for (; step; step /= 2) if (p + step <= n && f[p + step] < target) {
            target -= f[p + step]; p += step;
        }
        return p + 1;
    }
};
int main(int argc, char **argv) {
    if (argc != 2) return 2;
    int kind = std::atoi(argv[1]);
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n, q = 0, c = 0; std::cin >> n;
    if (kind == 193) { c = n; std::cin >> n >> q; }
    else if (kind != 122) std::cin >> q;
    std::vector<i64> a(n + 1);
    if (kind == 174) {
        std::string text; std::cin >> text;
        for (int i = 1; i <= n; ++i) a[i] = 1 << (text[i - 1] - 'a');
    } else for (int i = 1; i <= n; ++i) std::cin >> a[i];
    if (kind == 122) {
        Fenwick unused(n); std::vector<int> answer(n + 1);
        for (int i = 1; i <= n; ++i) unused.add(i, 1);
        for (int i = n; i >= 1; --i) { answer[i] = unused.select(i - a[i]); unused.add(answer[i], -1); }
        for (int i = 1; i <= n; ++i) std::cout << answer[i] << (i == n ? '\n' : ' ');
        return 0;
    }
    if (kind == 193) {
        std::multiset<int> boxes;
        for (int i = 1; i <= n; ++i) boxes.insert(int(a[i]));
        while (q--) {
            int t, x; std::cin >> t >> x;
            if (t == 1) boxes.insert(x);
            else {
                auto it = boxes.lower_bound(x);
                if (it == boxes.end()) std::cout << -1 << '\n';
                else { int capacity = *it; std::cout << capacity << '\n'; boxes.erase(it); boxes.insert(capacity - x); }
            }
        }
        return c < 1;
    }
    std::set<int> positions;
    if (kind == 112 || kind == 192) for (int i = 1; i <= n; ++i)
        if (a[i] == (kind == 112 ? 1 : 0)) positions.insert(i);
    Fenwick sums(n);
    if (kind == 132 || kind == 182) for (int i = 1; i <= n; ++i) sums.add(i, a[i]);
    const int B = 450;
    std::vector<i64> blocks((n + B - 1) / B);
    auto merge = [kind](i64 x, i64 y) -> i64 {
        if (kind == 102 || kind == 174) return x | y;
        if (kind == 173) return capped(x, y);
        return std::gcd(x, y);
    };
    auto rebuild = [&](int id) {
        i64 value = kind == 173 ? 1 : 0;
        for (int i = id * B + 1; i <= std::min(n, (id + 1) * B); ++i) value = merge(value, a[i]);
        blocks[id] = value;
    };
    if (kind == 102 || kind == 162 || kind == 173 || kind == 174 || kind == 182)
        for (int i = 0; i < int(blocks.size()); ++i) rebuild(i);
    while (q--) {
        int t; std::cin >> t;
        if (kind == 112) {
            int p; std::cin >> p;
            if (t == 1) { if (positions.count(p)) positions.erase(p); else positions.insert(p); }
            else {
                int answer = -1; auto it = positions.lower_bound(p);
                if (it != positions.end()) answer = *it;
                if (it != positions.begin()) { int left = *std::prev(it); if (answer == -1 || p - left <= answer - p) answer = left; }
                std::cout << answer << '\n';
            }
            continue;
        }
        if (kind == 192) {
            int p; std::cin >> p;
            if (t == 2) positions.insert(p);
            else if (positions.empty()) std::cout << -1 << '\n';
            else {
                auto it = positions.lower_bound(p); if (it == positions.end()) it = positions.begin();
                std::cout << *it << '\n'; positions.erase(it);
            }
            continue;
        }
        if (t == 1) {
            int p; i64 x; std::cin >> p;
            if (kind == 174) { char letter; std::cin >> letter; x = 1 << (letter - 'a'); }
            else std::cin >> x;
            if (kind == 132 || kind == 182) sums.add(p, x - a[p]);
            a[p] = x;
            if (kind != 132) rebuild((p - 1) / B);
            continue;
        }
        if (kind == 132) {
            i64 total = sums.sum(n); int p = -1, r = -1;
            if (total == 0) { p = 1; r = 2; }
            else if (total % 3 == 0) {
                p = sums.select(total / 3); r = sums.select(2 * (total / 3));
                if (r >= n || sums.sum(p) != total / 3 || sums.sum(r) != 2 * (total / 3)) p = r = -1;
            }
            std::cout << p << ' ' << r << '\n'; continue;
        }
        int l = 1, r = n, sum_position = -1; i64 target;
        if (kind == 102) std::cin >> target;
        else {
            std::cin >> l;
            if (kind == 162) std::cin >> r;
            std::cin >> target;
            if (kind == 182) {
                i64 required_sum = target + sums.sum(l - 1); std::cin >> target;
                if (sums.sum(n) < required_sum) { std::cout << -1 << '\n'; continue; }
                sum_position = sums.select(required_sum);
            }
        }
        i64 accumulated = kind == 173 ? 1 : 0;
        int pos = l;
        for (; pos <= r;) {
            int id = (pos - 1) / B, end = std::min(n, (id + 1) * B);
            i64 candidate = merge(accumulated, blocks[id]);
            bool skip = false;
            if (pos == id * B + 1 && end <= r) {
                if (kind == 102) skip = (blocks[id] & target) == 0;
                if (kind == 162) skip = blocks[id] % target == 0;
                if (kind == 173) skip = candidate <= target;
                if (kind == 174) skip = __builtin_popcount(static_cast<unsigned>(candidate)) <= target;
                if (kind == 182) skip = candidate > target;
            }
            if (skip) { accumulated = candidate; pos = end + 1; continue; }
            accumulated = merge(accumulated, a[pos]);
            if ((kind == 102 && (a[pos] & target) != 0) ||
                (kind == 162 && a[pos] % target != 0) ||
                (kind == 173 && accumulated > target) ||
                (kind == 174 && __builtin_popcount(static_cast<unsigned>(accumulated)) > target) ||
                (kind == 182 && accumulated <= target)) break;
            ++pos;
        }
        int answer = kind == 173 || kind == 174 ? pos - 1 : pos <= r ? pos : -1;
        if (kind == 182 && answer != -1) answer = std::max(answer, sum_position);
        std::cout << answer << '\n';
    }
}
