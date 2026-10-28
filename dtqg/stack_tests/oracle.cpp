#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

void second_sum() {
    int n; cin >> n;
    vector<int> a(n), position(n + 1);
    for (int i = 0; i < n; ++i) { cin >> a[i]; position[a[i]] = i; }
    set<int> larger{-1, n};
    ll answer = 0;
    for (int value = n; value >= 1; --value) {
        int i = position[value];
        auto right = larger.lower_bound(i), left = prev(right);
        int r1 = *right, r2 = r1 == n ? n : *next(right);
        int l1 = *left, l2 = l1 == -1 ? -1 : *prev(left);
        answer += value * (1LL * (l1 - l2) * (r1 - i) + 1LL * (i - l1) * (r2 - r1));
        larger.insert(i);
    }
    if (n <= 3000) {
        ll brute = 0;
        for (int l = 0; l < n; ++l) {
            int best = 0, runner_up = 0;
            for (int r = l; r < n; ++r) {
                if (a[r] > best) { runner_up = best; best = a[r]; }
                else runner_up = max(runner_up, a[r]);
                if (r > l) brute += runner_up;
            }
        }
        assert(brute == answer);
    }
    cout << answer << '\n';
}

void rectangles() {
    int rows, columns; cin >> rows >> columns;
    vector<string> board(rows);
    for (auto &s : board) cin >> s;
    vector<int> height(columns), left(columns), right(columns), stack;
    __int128_t answer = 0;
    for (int row = 0; row < rows; ++row) {
        for (int j = 0; j < columns; ++j) height[j] = board[row][j] == '1' ? height[j] + 1 : 0;
        stack.clear();
        for (int j = 0; j < columns; ++j) {
            while (!stack.empty() && height[stack.back()] >= height[j]) stack.pop_back();
            left[j] = stack.empty() ? -1 : stack.back(); stack.push_back(j);
        }
        stack.clear();
        for (int j = columns - 1; j >= 0; --j) {
            while (!stack.empty() && height[stack.back()] > height[j]) stack.pop_back();
            right[j] = stack.empty() ? columns : stack.back(); stack.push_back(j);
        }
        for (int j = 0; j < columns; ++j) {
            ll a = j - left[j], b = right[j] - j, h = height[j];
            answer += __int128_t(h) * (h + 1) / 2 * a * b * (a + b) / 2;
        }
    }
    if (1LL * min(rows, columns) * rows * columns <= 3000000) {
        if (rows > columns) {
            vector<string> transpose(columns, string(rows, '0'));
            for (int i = 0; i < rows; ++i) for (int j = 0; j < columns; ++j) transpose[j][i] = board[i][j];
            board.swap(transpose); swap(rows, columns);
        }
        ll brute = 0;
        for (int top = 0; top < rows; ++top) {
            vector<char> good(columns, true);
            for (int bottom = top; bottom < rows; ++bottom) {
                ll run = 0;
                for (int j = 0; j <= columns; ++j) {
                    if (j < columns) good[j] = good[j] && board[bottom][j] == '1';
                    if (j < columns && good[j]) ++run;
                    else { brute += (bottom - top + 1LL) * run * (run + 1) * (run + 2) / 6; run = 0; }
                }
            }
        }
        assert(answer == brute);
    }
    assert(answer >= 0 && answer < __int128_t(4000000000000000000LL));
    cout << ll(answer) << '\n';
}

struct HistoryTree {
    struct Node { ll current = 0, total = 0, a = 1, b = 0, c = 0, d = 0; };
    int n;
    vector<Node> t;
    explicit HistoryTree(int size) : n(size), t(4 * size) {}
    void apply(int u, int len, ll a, ll b, ll c, ll d) {
        ll old_a = t[u].a, old_b = t[u].b;
        t[u].total += c * t[u].current + d * len;
        t[u].current = a * t[u].current + b * len;
        t[u].c += c * old_a; t[u].d += c * old_b + d;
        t[u].a = a * old_a; t[u].b = a * old_b + b;
    }
    void push(int u, int l, int r) {
        if (l == r) return;
        int mid = (l + r) / 2;
        auto tag = t[u];
        apply(2 * u, mid - l + 1, tag.a, tag.b, tag.c, tag.d);
        apply(2 * u + 1, r - mid, tag.a, tag.b, tag.c, tag.d);
        t[u].a = 1; t[u].b = t[u].c = t[u].d = 0;
    }
    void assign(int u, int l, int r, int ql, int qr, ll x) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) { apply(u, r - l + 1, 0, x, 0, 0); return; }
        push(u, l, r); int mid = (l + r) / 2;
        assign(2 * u, l, mid, ql, qr, x); assign(2 * u + 1, mid + 1, r, ql, qr, x);
        t[u].current = t[2 * u].current + t[2 * u + 1].current;
        t[u].total = t[2 * u].total + t[2 * u + 1].total;
    }
    ll query(int u, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return t[u].total;
        push(u, l, r); int mid = (l + r) / 2;
        return query(2 * u, l, mid, ql, qr) + query(2 * u + 1, mid + 1, r, ql, qr);
    }
};

void windows() {
    int n, q; cin >> n >> q;
    vector<ll> a(n + 1), answer(q);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<pair<int, int>> original(q);
    vector<vector<pair<int, int>>> queries(n + 1);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r; original[i] = {l, r}; queries[r].push_back({l, i});
    }
    int size = 1; while (size < n) size *= 2;
    vector<ll> minimum(2 * size, 2000000000LL);
    HistoryTree tree(n);
    for (int r = 1; r <= n; ++r) {
        int p = 0;
        if (minimum[1] < a[r]) {
            int u = 1;
            while (u < size) u = minimum[2 * u + 1] < a[r] ? 2 * u + 1 : 2 * u;
            p = u - size + 1;
        }
        tree.assign(1, 1, n, p + 1, r, a[r]);
        tree.apply(1, n, 1, 0, 1, 0);
        int pos = size + r - 1; minimum[pos] = a[r];
        for (pos /= 2; pos; pos /= 2) minimum[pos] = min(minimum[2 * pos], minimum[2 * pos + 1]);
        for (auto [l, id] : queries[r]) answer[id] = tree.query(1, 1, n, l, r);
    }
    if (n <= 100 && q <= 500) {
        for (int id = 0; id < q; ++id) {
            auto [l, r] = original[id]; ll brute = 0;
            for (int i = l; i <= r; ++i) {
                ll value = a[i];
                for (int j = i; j <= r; ++j) { value = min(value, a[j]); brute += value; }
            }
            assert(answer[id] == brute);
        }
    }
    for (ll value : answer) cout << value << '\n';
}

struct PersistentAssign {
    struct Node { int l = 0, r = 0; ll sum = 0, fallback = 0; };
    deque<Node> t{Node{}};
    int assign(int old, int l, int r, int ql, int qr, ll x, ll inherited = 0) {
        if (ql > r || qr < l) return old;
        Node copy = old ? t[old] : Node{0, 0, inherited * (r - l + 1), inherited};
        int u = int(t.size()); t.push_back(copy);
        if (ql <= l && r <= qr) { t[u] = {0, 0, x * (r - l + 1), x}; return u; }
        int mid = (l + r) / 2;
        t[u].l = assign(t[u].l, l, mid, ql, qr, x, t[u].fallback);
        t[u].r = assign(t[u].r, mid + 1, r, ql, qr, x, t[u].fallback);
        t[u].sum = (t[u].l ? t[t[u].l].sum : t[u].fallback * (mid - l + 1))
                 + (t[u].r ? t[t[u].r].sum : t[u].fallback * (r - mid));
        return u;
    }
    ll query(int u, int l, int r, int ql, int qr, ll inherited = 0) const {
        if (ql > r || qr < l) return 0;
        if (!u) return inherited * (min(r, qr) - max(l, ql) + 1);
        if (ql <= l && r <= qr) return t[u].sum;
        int mid = (l + r) / 2;
        return query(t[u].l, l, mid, ql, qr, t[u].fallback)
             + query(t[u].r, mid + 1, r, ql, qr, t[u].fallback);
    }
};

void paths() {
    const int LOG = 20;
    int n, q; cin >> n >> q;
    vector<ll> a(n + 1, 2000000000LL);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) { int u, v; cin >> u >> v; adj[u].push_back(v); adj[v].push_back(u); }
    vector<int> parent(n + 1), depth(n + 1), order{1}, root(n + 1);
    depth[1] = 1;
    for (int i = 0; i < n; ++i) for (int v : adj[order[i]]) if (v != parent[order[i]]) {
        parent[v] = order[i]; depth[v] = depth[order[i]] + 1; order.push_back(v);
    }
    vector<array<int, LOG>> up(n + 1);
    vector<array<ll, LOG>> low(n + 1);
    low[0].fill(2000000000LL);
    PersistentAssign tree;
    for (int v : order) {
        up[v][0] = parent[v]; low[v][0] = a[v];
        for (int j = 1; j < LOG; ++j) {
            up[v][j] = up[up[v][j - 1]][j - 1];
            low[v][j] = min(low[v][j - 1], low[up[v][j - 1]][j - 1]);
        }
        int p = parent[v];
        for (int j = LOG - 1; j >= 0; --j)
            if (p && (1 << j) <= depth[p] && low[p][j] >= a[v]) p = up[p][j];
        root[v] = tree.assign(root[parent[v]], 1, n, depth[p] + 1, depth[v], a[v]);
    }
    vector<pair<int, int>> queries(q); ll steps = 0;
    for (auto &[v, k] : queries) { cin >> v >> k; steps += k; }
    bool brute = steps <= 3000000;
    for (auto [v, k] : queries) {
        ll answer = tree.query(root[v], 1, n, depth[v] - k + 1, depth[v]);
        if (brute) {
            ll slow = 0, best = 2000000000LL; int u = v;
            for (int i = 0; i < k; ++i) { best = min(best, a[u]); slow += best; u = parent[u]; }
            assert(slow == answer);
        }
        cout << answer << '\n';
    }
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int kind = argc > 1 ? atoi(argv[1]) : 0;
    if (kind == 1) second_sum();
    else if (kind == 2) rectangles();
    else if (kind == 3) windows();
    else if (kind == 4) paths();
    else return 1;
}
