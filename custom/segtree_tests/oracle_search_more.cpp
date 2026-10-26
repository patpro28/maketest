// Independent references: Fenwick trees, ordered boundaries and square-root blocks.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using i64 = long long;
struct Fenwick {
    int n; std::vector<i64> f;
    explicit Fenwick(int size) : n(size), f(size + 1) {}
    void add(int i, i64 x) { for (; i <= n; i += i & -i) f[i] += x; }
    i64 sum(int i) const { i64 s = 0; for (; i; i -= i & -i) s += f[i]; return s; }
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
    const int kind = std::atoi(argv[1]);
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n, q, d = 1; std::cin >> n >> q;
    if (kind == 161) std::cin >> d;
    if (kind == 191) {
        Fenwick alive(n); for (int i = 1; i <= n; ++i) alive.add(i, 1);
        i64 cursor = 0;
        for (int left = n; q--; --left) {
            i64 k; std::cin >> k; cursor = (cursor + k - 1) % left;
            int p = alive.select(cursor + 1); std::cout << p << '\n'; alive.add(p, -1);
            if (left > 1) cursor %= left - 1;
        }
        return 0;
    }
    int size = n + (kind == 101);
    std::vector<i64> a(size + 1), b(size + 1);
    for (int i = 1; i <= size; ++i) std::cin >> a[i];
    if (kind == 181) for (int i = 1; i <= n; ++i) std::cin >> b[i];
    Fenwick first(size), second(size);
    std::set<int> drops;
    const int B = 450;
    std::vector<i64> block((size + B - 1) / B);
    auto rebuild = [&](int id) {
        i64 v = kind == 151 ? 2000000000LL : 0;
        for (int i = id * B + 1; i <= std::min(size, (id + 1) * B); ++i) {
            if (kind == 151) v = std::min(v, a[i]);
            if (kind == 171) v = std::gcd(v, a[i]);
            if (kind == 172) v |= a[i];
        }
        block[id] = v;
    };
    for (int id = 0; id < int(block.size()); ++id) rebuild(id);
    for (int i = 1; i <= size; ++i) {
        if (kind == 101) first.add(i, a[i] == 0);
        if (kind == 121 || kind == 131 || kind == 181) first.add(i, a[i]);
        if (kind == 161) first.add(i, a[i] % d == 0);
        if (kind == 181) second.add(i, b[i]);
        if (kind == 111 && i < n && a[i] > a[i + 1]) drops.insert(i);
    }
    while (q--) {
        int t; std::cin >> t;
        if (kind == 101) {
            int x; std::cin >> x; ++x;
            first.add(x, -(a[x] == 0)); a[x] += t == 1 ? 1 : -1; first.add(x, a[x] == 0);
            std::cout << (first.sum(size) == 0 ? n + 1 : first.select(1) - 1) << '\n'; continue;
        }
        if (kind == 121) {
            if (t == 1) { int p; i64 x; std::cin >> p >> x; first.add(p, x); }
            else {
                i64 k; std::cin >> k;
                if (first.sum(n) < k) std::cout << -1 << '\n';
                else { int p = first.select(k); std::cout << p << '\n'; first.add(p, -1); }
            }
            continue;
        }
        int l; std::cin >> l;
        if (t == 1) {
            i64 x; std::cin >> x;
            if (kind == 131 || kind == 181) first.add(l, x - a[l]);
            if (kind == 161) first.add(l, int(x % d == 0) - int(a[l] % d == 0));
            a[l] = x;
            if (kind == 181) { i64 y; std::cin >> y; second.add(l, y - b[l]); b[l] = y; }
            if (kind == 111) for (int p : {l - 1, l}) if (p >= 1 && p < n) {
                drops.erase(p); if (a[p] > a[p + 1]) drops.insert(p);
            }
            if (kind == 151 || kind == 171 || kind == 172) rebuild((l - 1) / B);
            continue;
        }
        if (kind == 111) {
            int r; std::cin >> r; auto it = drops.lower_bound(l);
            std::cout << (it != drops.end() && *it < r ? *it : -1) << '\n';
        } else if (kind == 131) {
            int r; std::cin >> r; i64 before = first.sum(l - 1), w = first.sum(r) - before;
            std::cout << (w ? first.select(before + (w + 1) / 2) : l) << '\n';
        } else if (kind == 161) {
            int r; i64 k; std::cin >> r >> k; i64 before = first.sum(l - 1);
            std::cout << (first.sum(r) - before < k ? -1 : first.select(before + k)) << '\n';
        } else if (kind == 181) {
            i64 s, k; std::cin >> s >> k; s += first.sum(l - 1); k += second.sum(l - 1);
            std::cout << (first.sum(n) < s || second.sum(n) < k ? -1 : std::max(first.select(s), second.select(k))) << '\n';
        } else {
            i64 target;
            int start = l;
            if (kind == 151) { target = a[l]; ++start; } else std::cin >> target;
            i64 aggregate = 0; int pos = start;
            for (; pos <= n;) {
                int id = (pos - 1) / B, end = std::min(n, (id + 1) * B);
                bool skip = false;
                i64 candidate = aggregate;
                if (pos == id * B + 1) {
                    if (kind == 151) skip = block[id] >= target;
                    if (kind == 171) { candidate = std::gcd(aggregate, block[id]); skip = candidate >= target; }
                    if (kind == 172) { candidate = aggregate | block[id]; skip = (candidate & target) != target; }
                }
                if (skip) { aggregate = candidate; pos = end + 1; continue; }
                if (kind == 151 && a[pos] < target) break;
                if (kind == 171) { aggregate = std::gcd(aggregate, a[pos]); if (aggregate < target) break; }
                if (kind == 172) { aggregate |= a[pos]; if ((aggregate & target) == target) break; }
                ++pos;
            }
            std::cout << (kind == 171 ? pos - 1 : pos <= n ? pos : -1) << '\n';
        }
    }
}
