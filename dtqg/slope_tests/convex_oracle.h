#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

// Test-only representation f(x)=B-S*x+sum w*(x-a)_+.
// Unlike the reference two-heap solutions, it stores all derivative events.
struct ConvexOracle {
    using ll = long long;
    using i128 = __int128_t;
    struct Node {
        int l = 0, r = 0;
        uint64_t priority = 0;
        ll x = 0, w = 0, mass = 0, lazy = 0;
        i128 moment = 0;
    };
    struct Function { int root = 0; ll slope = 0; i128 intercept = 0; };
    std::vector<Node> t{Node{}};
    uint64_t state = 0xe419b370e9a42635ULL;
    explicit ConvexOracle(int n) { t.reserve(4 * n + 10); }
    ll mass(int u) const { return t[u].mass; }
    i128 moment(int u) const { return t[u].moment; }
    void pull(int u) {
        t[u].mass = mass(t[u].l) + t[u].w + mass(t[u].r);
        t[u].moment = moment(t[u].l) + i128(t[u].x) * t[u].w + moment(t[u].r);
    }
    void shift(int u, ll dx) {
        if (!u) return;
        t[u].x += dx; t[u].lazy += dx; t[u].moment += i128(dx) * t[u].mass;
    }
    void push(int u) {
        if (t[u].lazy) {
            shift(t[u].l, t[u].lazy); shift(t[u].r, t[u].lazy); t[u].lazy = 0;
        }
    }
    int create(ll x, ll w) {
        state ^= state << 13; state ^= state >> 7; state ^= state << 17;
        Node a; a.x = x; a.w = a.mass = w; a.moment = i128(x) * w; a.priority = state;
        t.push_back(a); return int(t.size()) - 1;
    }
    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].priority > t[b].priority) {
            push(a); t[a].r = merge(t[a].r, b); pull(a); return a;
        }
        push(b); t[b].l = merge(a, t[b].l); pull(b); return b;
    }
    std::pair<int, int> split_key(int u, ll key) {
        if (!u) return {0, 0};
        push(u);
        if (t[u].x <= key) {
            auto [a, b] = split_key(t[u].r, key); t[u].r = a; pull(u); return {u, b};
        }
        auto [a, b] = split_key(t[u].l, key); t[u].l = b; pull(u); return {a, u};
    }
    std::pair<int, int> split_mass(int u, ll k) {
        if (!u || k == 0) return {0, u};
        if (k >= mass(u)) return {u, 0};
        push(u);
        ll before = mass(t[u].l);
        if (k < before) {
            auto [a, b] = split_mass(t[u].l, k); t[u].l = b; pull(u); return {a, u};
        }
        if (k > before + t[u].w) {
            auto [a, b] = split_mass(t[u].r, k - before - t[u].w); t[u].r = a; pull(u); return {u, b};
        }
        if (k == before) { int a = t[u].l; t[u].l = 0; pull(u); return {a, u}; }
        if (k == before + t[u].w) { int b = t[u].r; t[u].r = 0; pull(u); return {u, b}; }
        ll used = k - before, rest = t[u].w - used;
        int right = t[u].r;
        t[u].r = 0; t[u].w = used; pull(u);
        int copy = create(t[u].x, rest);
        return {u, merge(copy, right)};
    }
    int event(int root, ll x, ll w) {
        auto [a, bc] = split_key(root, x - 1);
        auto [b, c] = split_key(bc, x);
        int middle = create(x, w + mass(b));
        return merge(merge(a, middle), c);
    }
    int unite(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].priority < t[b].priority) std::swap(a, b);
        push(a);
        auto [lower, rest] = split_key(b, t[a].x - 1);
        auto [equal, upper] = split_key(rest, t[a].x);
        t[a].w += mass(equal);
        t[a].l = unite(t[a].l, lower); t[a].r = unite(t[a].r, upper);
        pull(a); return a;
    }
    void interval(Function& f, ll l, ll r) {
        f.intercept += l; ++f.slope;
        f.root = event(f.root, l, 1); f.root = event(f.root, r, 1);
    }
    void absolute(Function& f, ll a) {
        f.intercept += a; ++f.slope; f.root = event(f.root, a, 2);
    }
    void window(Function& f, ll u, ll v) {
        auto [left, right] = split_mass(f.root, f.slope);
        shift(left, -u); shift(right, v);
        f.root = merge(left, right); f.intercept -= i128(f.slope) * u;
    }
    void add(Function& a, Function& b) {
        a.root = unite(a.root, b.root); a.slope += b.slope; a.intercept += b.intercept;
        b = Function{};
    }
    ll minimum(Function& f) {
        if (!f.slope) return ll(f.intercept);
        assert(mass(f.root) == 2 * f.slope);
        int u = f.root; ll k = f.slope, x = 0;
        while (u) {
            push(u);
            if (k <= mass(t[u].l)) u = t[u].l;
            else if (k <= mass(t[u].l) + t[u].w) { x = t[u].x; break; }
            else { k -= mass(t[u].l) + t[u].w; u = t[u].r; }
        }
        i128 answer = f.intercept - i128(f.slope) * x;
        u = f.root;
        while (u) {
            push(u);
            if (t[u].x > x) u = t[u].l;
            else {
                answer += i128(x) * (mass(t[u].l) + t[u].w) - moment(t[u].l) - i128(t[u].x) * t[u].w;
                u = t[u].r;
            }
        }
        assert(answer >= 0 && answer < i128(4000000000000000000LL));
        return ll(answer);
    }
};
