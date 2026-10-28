#include <algorithm>
#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 4000000000000000000LL;

struct DSU {
    vector<int> p, size;
    vector<ll> red, blue;
    ll pairs = 0;
    explicit DSU(int n) : p(n), size(n, 1), red(n), blue(n) { iota(p.begin(), p.end(), 0); }
    explicit DSU(const vector<int>& c) : DSU(int(c.size())) {
        for (int i = 0; i < int(c.size()); ++i) { red[i] = c[i] == 0; blue[i] = c[i] == 1; }
    }
    int find(int x) {
        while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
        return x;
    }
    void merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        pairs += red[a] * blue[b] + blue[a] * red[b];
        p[b] = a; size[a] += size[b]; red[a] += red[b]; blue[a] += blue[b];
    }
};

void network() {
    int n, q; cin >> n >> q;
    vector<int> color(n);
    for (auto &c : color) cin >> c;
    struct Op { char type; int id; };
    vector<Op> ops(q);
    vector<pair<int, int>> edges;
    map<pair<int, int>, int> id;
    bool has_delete = false;
    for (auto &op : ops) {
        cin >> op.type; op.id = -1;
        if (op.type == '?') continue;
        int u, v; cin >> u >> v; --u; --v;
        if (u > v) swap(u, v);
        auto edge = make_pair(u, v);
        if (!id.count(edge)) { int next = int(edges.size()); id[edge] = next; edges.push_back(edge); }
        op.id = id[edge];
        has_delete |= op.type == '-';
    }
    int m = int(edges.size());
    vector<char> active(m);
    if (n <= 3000 && q <= 3000) {
        for (auto op : ops) {
            if (op.type != '?') { active[op.id] = op.type == '+'; continue; }
            vector<vector<int>> adj(n);
            for (int i = 0; i < m; ++i) if (active[i]) {
                auto [u, v] = edges[i]; adj[u].push_back(v); adj[v].push_back(u);
            }
            vector<char> seen(n);
            ll answer = 0;
            for (int s = 0; s < n; ++s) if (!seen[s]) {
                ll red = 0, blue = 0;
                vector<int> todo{s}; seen[s] = true;
                for (int i = 0; i < int(todo.size()); ++i) {
                    int u = todo[i];
                    if (color[u]) ++blue; else ++red;
                    for (int v : adj[u]) if (!seen[v]) { seen[v] = true; todo.push_back(v); }
                }
                answer += red * blue;
            }
            cout << answer << '\n';
        }
        return;
    }
    if (!has_delete) {
        DSU dsu(color);
        for (auto op : ops) {
            if (op.type == '?') cout << dsu.pairs << '\n';
            else dsu.merge(edges[op.id].first, edges[op.id].second);
        }
        return;
    }
    // Independent square-root decomposition, with no rollback or time tree.
    const int BLOCK = 700;
    vector<char> changing(m);
    for (int start = 0; start < q; start += BLOCK) {
        int end = min(q, start + BLOCK);
        vector<int> volatile_edges;
        for (int i = start; i < end; ++i) if (ops[i].id >= 0 && !changing[ops[i].id]) {
            changing[ops[i].id] = true; volatile_edges.push_back(ops[i].id);
        }
        DSU base(color);
        for (int e = 0; e < m; ++e) if (active[e] && !changing[e])
            base.merge(edges[e].first, edges[e].second);
        vector<int> root_index(n, -1), roots, local_u, local_v;
        auto index = [&](int u) {
            int r = base.find(u);
            if (root_index[r] == -1) { root_index[r] = int(roots.size()); roots.push_back(r); }
            return root_index[r];
        };
        for (int e : volatile_edges) {
            local_u.push_back(index(edges[e].first));
            local_v.push_back(index(edges[e].second));
        }
        DSU local(int(roots.size()));
        for (int i = start; i < end; ++i) {
            auto op = ops[i];
            if (op.type != '?') { active[op.id] = op.type == '+'; continue; }
            iota(local.p.begin(), local.p.end(), 0);
            fill(local.size.begin(), local.size.end(), 1);
            local.pairs = base.pairs;
            for (int j = 0; j < int(roots.size()); ++j) {
                local.red[j] = base.red[roots[j]]; local.blue[j] = base.blue[roots[j]];
            }
            for (int j = 0; j < int(volatile_edges.size()); ++j)
                if (active[volatile_edges[j]]) local.merge(local_u[j], local_v[j]);
            cout << local.pairs << '\n';
        }
        for (int e : volatile_edges) changing[e] = false;
    }
}

void message() {
    int m; ll length; cin >> m >> length;
    vector<pair<string, ll>> patterns(m);
    for (auto &p : patterns) cin >> p.first >> p.second;
    if (length <= 8) {
        ll answer = -INF;
        string text;
        auto enumerate = [&](auto&& self) -> void {
            if (int(text.size()) == length) {
                ll score = 0;
                for (auto [s, w] : patterns)
                    for (int i = 0; i + int(s.size()) <= int(text.size()); ++i)
                        if (text.compare(i, s.size(), s) == 0) score += w;
                answer = max(answer, score); return;
            }
            for (char c : string("abc")) { text += c; self(self); text.pop_back(); }
        };
        enumerate(enumerate); cout << answer << '\n'; return;
    }
    // Build suffix states by literal string comparisons, not failure links.
    set<string> all{""};
    for (auto [s, w] : patterns) for (int i = 1; i <= int(s.size()); ++i) all.insert(s.substr(0, i));
    vector<string> state(all.begin(), all.end());
    int n = int(state.size());
    vector<array<int, 3>> next(n);
    vector<array<ll, 3>> reward(n);
    for (int u = 0; u < n; ++u) for (int c = 0; c < 3; ++c) {
        string suffix = state[u] + char('a' + c);
        int best = 0;
        for (int v = 0; v < n; ++v)
            if (state[v].size() <= suffix.size() && state[v].size() > state[best].size()
                && suffix.compare(suffix.size() - state[v].size(), state[v].size(), state[v]) == 0) best = v;
        next[u][c] = best;
        reward[u][c] = 0;
        for (auto [s, w] : patterns)
            if (s.size() <= suffix.size() && suffix.compare(suffix.size() - s.size(), s.size(), s) == 0)
                reward[u][c] += w;
    }
    vector<ll> best(n, -INF); best[0] = 0;
    if (length <= 100000) {
        for (ll i = 0; i < length; ++i) {
            vector<ll> other(n, -INF);
            for (int u = 0; u < n; ++u) if (best[u] != -INF)
                for (int c = 0; c < 3; ++c)
                    other[next[u][c]] = max(other[next[u][c]], best[u] + reward[u][c]);
            best.swap(other);
        }
    } else {
        // Column-vector convention, independently constructed transition matrix.
        using Matrix = vector<vector<ll>>;
        Matrix a(n, vector<ll>(n, -INF));
        for (int u = 0; u < n; ++u) for (int c = 0; c < 3; ++c)
            a[next[u][c]][u] = max(a[next[u][c]][u], reward[u][c]);
        while (length) {
            if (length % 2) {
                vector<ll> other(n, -INF);
                for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
                    if (a[i][j] != -INF && best[j] != -INF) other[i] = max(other[i], a[i][j] + best[j]);
                best.swap(other);
            }
            length /= 2;
            if (!length) break;
            Matrix square(n, vector<ll>(n, -INF));
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    if (a[i][k] != -INF && a[k][j] != -INF)
                        square[i][j] = max(square[i][j], a[i][k] + a[k][j]);
            a.swap(square);
        }
    }
    cout << *max_element(best.begin(), best.end()) << '\n';
}

void batches() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    if (n <= 14) {
        ll answer = INF;
        for (int mask = 0; mask < (1 << (n - 1)); ++mask) if (__builtin_popcount(unsigned(mask)) == k - 1) {
            vector<int> f(n + 1);
            ll value = 0;
            for (int i = 0; i < n; ++i) {
                value += f[a[i]]++;
                if (i < n - 1 && (mask >> i & 1)) fill(f.begin(), f.end(), 0);
            }
            answer = min(answer, value);
        }
        cout << answer << '\n'; return;
    }
    if (n <= 3000) {
        vector<int> cost((n + 1) * (n + 1)), f(n + 1);
        for (int r = 1; r <= n; ++r) {
            fill(f.begin(), f.end(), 0);
            int total = 0;
            for (int l = r; l >= 1; --l) { total += f[a[l - 1]]++; cost[r * (n + 1) + l] = total; }
        }
        vector<ll> dp(n + 1, INF); dp[0] = 0;
        for (int g = 1; g <= k; ++g) {
            vector<ll> other(n + 1, INF);
            for (int r = g; r <= n; ++r) for (int cut = g - 1; cut < r; ++cut)
                if (dp[cut] != INF) other[r] = min(other[r], dp[cut] + cost[r * (n + 1) + cut + 1]);
            dp.swap(other);
        }
        cout << dp[n] << '\n'; return;
    }
    vector<ll> count(n + 1);
    for (int x : a) ++count[x];
    if (k == 1) {
        ll answer = 0;
        for (ll f : count) answer += f * (f - 1) / 2;
        cout << answer << '\n'; return;
    }
    int period = n;
    for (int i = 1; i < n; ++i) if (a[i] == a[0]) { period = i; break; }
    bool periodic = true;
    set<int> first(a.begin(), a.begin() + period);
    periodic &= int(first.size()) == period;
    for (int i = 0; i < n; ++i) periodic &= a[i] == a[i % period];
    if (periodic) {
        auto cost = [&](ll len) { ll q = len / period, r = len % period; return period * q * (q - 1) / 2 + r * q; };
        ll q = n / k, r = n % k;
        cout << (k - r) * cost(q) + r * cost(q + 1) << '\n'; return;
    }
    // Second optimized implementation: reverse the input, scan cuts downwards,
    // choose rightmost ties and visit right subproblems before left ones.
    reverse(a.begin(), a.end());
    vector<ll> dp(n + 1, INF); dp[0] = 0;
    for (int g = 1; g <= k; ++g) {
        vector<ll> other(n + 1, INF);
        vector<int> f(n + 1);
        int low = 0, high = -1;
        ll current = 0;
        auto insert = [&](int x) { current += f[a[x]]++; };
        auto erase = [&](int x) { current -= --f[a[x]]; };
        auto cost = [&](int l, int r) {
            while (high < r) insert(++high);
            while (low > l) insert(--low);
            while (high > r) erase(high--);
            while (low < l) erase(low++);
            return current;
        };
        function<void(int,int,int,int)> divide = [&](int l, int r, int x, int y) {
            if (l > r) return;
            int mid = (l + r) / 2, opt = -1;
            for (int cut = min(y, mid - 1); cut >= x; --cut) {
                ll value = cost(cut, mid - 1);
                if (dp[cut] != INF && dp[cut] + value < other[mid]) {
                    other[mid] = dp[cut] + value; opt = cut;
                }
            }
            divide(mid + 1, r, opt, y);
            divide(l, mid - 1, x, opt);
        };
        divide(g, n, g - 1, n - 1);
        dp.swap(other);
    }
    cout << dp[n] << '\n';
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int kind = argc > 1 ? atoi(argv[1]) : 0;
    if (kind == 1) network();
    else if (kind == 2) message();
    else if (kind == 3) batches();
    else return 1;
}
