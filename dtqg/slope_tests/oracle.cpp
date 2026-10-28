#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>
#include "convex_oracle.h"
using namespace std;
using ll = long long;
const ll INF = 4000000000000000000LL;

struct Block {
    priority_queue<ll> lo;
    priority_queue<ll, vector<ll>, greater<ll>> hi;
    ll sum_lo = 0, sum_hi = 0;
    int size() const { return int(lo.size() + hi.size()); }
    void insert(ll x) {
        if (lo.empty() || x <= lo.top()) { lo.push(x); sum_lo += x; }
        else { hi.push(x); sum_hi += x; }
        if (lo.size() > hi.size() + 1) {
            ll v = lo.top(); lo.pop(); sum_lo -= v; hi.push(v); sum_hi += v;
        }
        if (lo.size() < hi.size()) {
            ll v = hi.top(); hi.pop(); sum_hi -= v; lo.push(v); sum_lo += v;
        }
    }
    void merge(Block& b) {
        if (size() < b.size()) swap(*this, b);
        while (!b.lo.empty()) { ll x = b.lo.top(); b.lo.pop(); insert(x); }
        while (!b.hi.empty()) { ll x = b.hi.top(); b.hi.pop(); insert(x); }
    }
    ll cost() const { return lo.top() * ll(lo.size()) - sum_lo + sum_hi - lo.top() * ll(hi.size()); }
};

void convoy() {
    int n; cin >> n;
    vector<ll> a(n), length(n), gap(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> length[i];
    for (int i = 0; i + 1 < n; ++i) cin >> gap[i];
    ll offset = 0;
    vector<unique_ptr<Block>> blocks;
    for (int i = 0; i < n; ++i) {
        if (i) offset += length[i - 1] + gap[i - 1];
        b[i] = a[i] - offset;
        auto p = make_unique<Block>(); p->insert(b[i]); blocks.push_back(std::move(p));
        while (blocks.size() > 1 && blocks[blocks.size() - 2]->lo.top() > blocks.back()->lo.top()) {
            auto last = std::move(blocks.back()); blocks.pop_back(); blocks.back()->merge(*last);
        }
    }
    ll answer = 0;
    for (const auto& block : blocks) answer += block->cost();
    if (n <= 3000) {
        auto values = b;
        sort(values.begin(), values.end()); values.erase(unique(values.begin(), values.end()), values.end());
        vector<ll> dp(values.size(), 0);
        for (ll target : b) {
            ll best = INF;
            for (int j = 0; j < int(values.size()); ++j) {
                best = min(best, dp[j]); dp[j] = best + llabs(values[j] - target);
            }
        }
        assert(answer == *min_element(dp.begin(), dp.end()));
    }
    cout << answer << '\n';
}

vector<ll> window_minimum(const vector<ll>& dp, ll u, ll v) {
    int width = int(dp.size()), added = -1;
    deque<int> queue;
    vector<ll> result(width);
    for (int x = 0; x < width; ++x) {
        int right = int(min<ll>(width - 1, x + u));
        while (added < right) {
            ++added;
            while (!queue.empty() && dp[queue.back()] >= dp[added]) queue.pop_back();
            queue.push_back(added);
        }
        ll left = max<ll>(0, x - v);
        while (!queue.empty() && queue.front() < left) queue.pop_front();
        result[x] = dp[queue.front()];
    }
    return result;
}

void tracking() {
    int n; cin >> n;
    vector<ll> l(n), r(n), u(n), v(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
    for (int i = 0; i + 1 < n; ++i) cin >> u[i] >> v[i];
    ConvexOracle tree(n); ConvexOracle::Function f;
    for (int i = 0; i < n; ++i) {
        if (i) tree.window(f, u[i - 1], v[i - 1]);
        tree.interval(f, l[i], r[i]);
    }
    ll answer = tree.minimum(f);
    ll low = *min_element(l.begin(), l.end()), high = *max_element(r.begin(), r.end());
    if (high - low <= 2000 && (high - low + 1) * n <= 3000000) {
        int width = int(high - low + 1);
        vector<ll> dp(width, 0);
        for (int i = 0; i < n; ++i) {
            if (i) dp = window_minimum(dp, u[i - 1], v[i - 1]);
            for (int j = 0; j < width; ++j) dp[j] += max(l[i] - (low + j), 0LL) + max((low + j) - r[i], 0LL);
        }
        assert(answer == *min_element(dp.begin(), dp.end()));
    }
    cout << answer << '\n';
}

struct Matrix {
    array<ll, 4> a{{0, INF, INF, 0}};
};
Matrix product(const Matrix& a, const Matrix& b) {
    Matrix c; c.a.fill(INF);
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k)
        if (a.a[2 * i + k] != INF && b.a[2 * k + j] != INF)
            c.a[2 * i + j] = min(c.a[2 * i + j], a.a[2 * i + k] + b.a[2 * k + j]);
    return c;
}

void signal() {
    int n; cin >> n;
    vector<ll> a(n), w(n), c(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> w[i];
    for (int i = 0; i + 1 < n; ++i) cin >> c[i];
    int size = 1;
    while (size < n) size *= 2;
    vector<Matrix> seg(2 * size);
    auto leaf = [&](int i, int preferred) {
        Matrix result;
        for (int before = 0; before < 2; ++before) for (int now = 0; now < 2; ++now)
            result.a[2 * before + now] = (now == preferred ? 0 : w[i]) + (i && before != now ? c[i - 1] : 0);
        return result;
    };
    for (int i = 0; i < n; ++i) seg[size + i] = leaf(i, 1);
    for (int i = size - 1; i; --i) seg[i] = product(seg[2 * i], seg[2 * i + 1]);
    vector<int> order(n); iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return a[i] < a[j]; });
    ll answer = 0;
    for (int start = 0; start < n;) {
        int end = start;
        ll value = a[order[start]];
        while (end < n && a[order[end]] == value) {
            int pos = size + order[end]; seg[pos] = leaf(order[end], 0);
            for (pos /= 2; pos; pos /= 2) seg[pos] = product(seg[2 * pos], seg[2 * pos + 1]);
            ++end;
        }
        if (end < n) answer += (a[order[end]] - value) * *min_element(seg[1].a.begin(), seg[1].a.end());
        start = end;
    }
    ll low = *min_element(a.begin(), a.end()), high = *max_element(a.begin(), a.end());
    if (high - low <= 2000 && (high - low + 1) * n <= 3000000) {
        int width = int(high - low + 1);
        vector<ll> dp(width);
        for (int j = 0; j < width; ++j) dp[j] = w[0] * llabs(low + j - a[0]);
        for (int i = 1; i < n; ++i) {
            auto left = dp, right = dp;
            for (int j = 1; j < width; ++j) left[j] = min(left[j], left[j - 1] + c[i - 1]);
            for (int j = width - 2; j >= 0; --j) right[j] = min(right[j], right[j + 1] + c[i - 1]);
            for (int j = 0; j < width; ++j) dp[j] = min(left[j], right[j]) + w[i] * llabs(low + j - a[i]);
        }
        assert(answer == *min_element(dp.begin(), dp.end()));
    }
    cout << answer << '\n';
}

void sensors() {
    int n; cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll d; cin >> u >> v >> d; --u; --v;
        adj[u].push_back({v, d}); adj[v].push_back({u, d});
    }
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) for (auto [v, d] : adj[order[i]]) if (v != parent[order[i]]) {
        parent[v] = order[i]; order.push_back(v); (void)d;
    }
    ConvexOracle tree(n);
    vector<ConvexOracle::Function> f(n);
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        for (auto [v, d] : adj[u]) if (parent[v] == u) {
            tree.window(f[v], d, d); tree.add(f[u], f[v]);
        }
        tree.absolute(f[u], a[u]);
    }
    ll answer = tree.minimum(f[0]);
    ll low = *min_element(a.begin(), a.end()), high = *max_element(a.begin(), a.end());
    if (high - low <= 2000 && (high - low + 1) * n <= 3000000) {
        int width = int(high - low + 1);
        vector<vector<ll>> dp(n);
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i]; dp[u].resize(width);
            for (int j = 0; j < width; ++j) dp[u][j] = llabs(low + j - a[u]);
            for (auto [v, d] : adj[u]) if (parent[v] == u) {
                auto best = window_minimum(dp[v], d, d);
                for (int j = 0; j < width; ++j) dp[u][j] += best[j];
            }
        }
        assert(answer == *min_element(dp[0].begin(), dp[0].end()));
    }
    cout << answer << '\n';
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int kind = argc > 1 ? atoi(argv[1]) : 0;
    if (kind == 1) convoy();
    else if (kind == 2) tracking();
    else if (kind == 3) signal();
    else if (kind == 4) sensors();
    else return 1;
}
