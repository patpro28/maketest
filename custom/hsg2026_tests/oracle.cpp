// Independent slow models: all-source tree traversal, last-edge Dijkstra,
// and direct prefix DP over all allowed last segments.
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 4000000000000000000LL;

void tree_oracle() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[--u].push_back({--v, w});
        adj[v].push_back({u, w});
    }
    if (n > 5000) {
        // Sum each edge's contribution to intervals in Euler order.
        // This uses no parent-to-child cost recurrence.
        vector<int> parent(n, -1), weight(n), tin(n), size(n, 1), order, stack{0};
        vector<ll> sub = a;
        while (!stack.empty()) {
            int u = stack.back(); stack.pop_back();
            tin[u] = int(order.size()); order.push_back(u);
            for (auto [v, w] : adj[u]) if (v != parent[u]) {
                parent[v] = u; weight[v] = w; stack.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; --i) {
            int u = order[i];
            sub[parent[u]] += sub[u]; size[parent[u]] += size[u];
        }
        ll total = sub[0], baseline = 0;
        vector<ll> diff(n + 1);
        for (int u = 1; u < n; ++u) {
            baseline += sub[u] * weight[u];
            ll change = (total - sub[u]) * weight[u] - sub[u] * weight[u];
            diff[tin[u]] += change;
            diff[tin[u] + size[u]] -= change;
        }
        pair<ll, int> best{INF, n};
        ll offset = 0;
        for (int i = 0; i < n; ++i) {
            offset += diff[i];
            int u = order[i];
            best = min(best, make_pair(baseline + offset + b[u], u));
        }
        cout << best.second + 1 << ' ' << best.first << '\n';
        return;
    }
    pair<ll, int> best{INF, n};
    for (int s = 0; s < n; ++s) {
        ll cost = b[s];
        vector<tuple<int, int, ll>> stack{{s, -1, 0}};
        while (!stack.empty()) {
            auto [u, parent, d] = stack.back(); stack.pop_back();
            cost += a[u] * d;
            for (auto [v, w] : adj[u]) if (v != parent)
                stack.push_back({v, u, d + w});
        }
        best = min(best, make_pair(cost, s));
    }
    cout << best.second + 1 << ' ' << best.first << '\n';
}

void route_oracle() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s; --t;
    vector<ll> fee(n);
    for (auto &x : fee) cin >> x;
    struct Edge { int u, v, c, w; };
    vector<Edge> edges;
    edges.reserve(m);
    vector<vector<int>> outgoing(n);
    for (int i = 0; i < m; ++i) {
        Edge e;
        cin >> e.u >> e.v >> e.c >> e.w;
        --e.u; --e.v;
        // A positive-length self-loop never improves a route: deleting it
        // cannot increase the number of line changes at that city.
        if (e.u == e.v) continue;
        outgoing[e.u].push_back(int(edges.size()));
        edges.push_back(e);
    }
    m = int(edges.size());
    if (s == t) { cout << 0 << '\n'; return; }
    if (m > 5000) {
        bool only_source_loops_or_direct = true;
        ll direct = INF;
        for (auto e : edges) {
            only_source_loops_or_direct &= e.u == s && (e.v == s || e.v == t);
            if (e.u == s && e.v == t) direct = min(direct, ll(e.w));
        }
        if (only_source_loops_or_direct) {
            // Positive travel times make all source loops unnecessary.
            cout << (direct == INF ? -1 : direct) << '\n';
            return;
        }
    }
    if ((n > 5000 || m > 5000) && !outgoing[s].empty()) {
        int hub = edges[outgoing[s][0]].v;
        bool two_hop = hub != s && hub != t;
        for (auto e : edges)
            two_hop &= (e.u == s && e.v == hub) || (e.u == hub && e.v == t);
        if (two_hop) {
            // Direct two-leg journey formula for the quadratic hub stress.
            map<int, ll> incoming;
            ll cheapest = INF, best = INF;
            for (int i : outgoing[s]) {
                auto e = edges[i];
                if (!incoming.count(e.c)) incoming[e.c] = INF;
                incoming[e.c] = min(incoming[e.c], ll(e.w));
                cheapest = min(cheapest, ll(e.w));
            }
            for (int i : outgoing[hub]) {
                auto e = edges[i];
                best = min(best, cheapest + fee[hub] + e.w);
                if (incoming.count(e.c)) best = min(best, incoming[e.c] + e.w);
            }
            cout << (best == INF ? -1 : best) << '\n';
            return;
        }
    }
    if (m > 5000) {
        // Independent DP on an original acyclic graph: process all incoming
        // line costs before considering any outgoing edge of a city.
        vector<int> indegree(n), order;
        for (auto e : edges) ++indegree[e.v];
        for (int u = 0; u < n; ++u) if (indegree[u] == 0) order.push_back(u);
        for (int i = 0; i < int(order.size()); ++i)
            for (int e : outgoing[order[i]])
                if (--indegree[edges[e].v] == 0) order.push_back(edges[e].v);
        if (int(order.size()) == n) {
            vector<map<int, ll>> arrival(n);
            vector<ll> cheapest(n, INF);
            cheapest[s] = 0;
            for (int u : order) {
                if (cheapest[u] == INF) continue;
                for (int i : outgoing[u]) {
                    auto e = edges[i];
                    ll cost = cheapest[u] + (u == s ? 0 : fee[u]);
                    auto it = arrival[u].find(e.c);
                    if (it != arrival[u].end()) cost = min(cost, it->second);
                    cost += e.w;
                    auto dest = arrival[e.v].find(e.c);
                    if (dest == arrival[e.v].end()) arrival[e.v][e.c] = cost;
                    else dest->second = min(dest->second, cost);
                    cheapest[e.v] = min(cheapest[e.v], cost);
                }
            }
            cout << (cheapest[t] == INF ? -1 : cheapest[t]) << '\n';
            return;
        }
    }
    vector<ll> d(m, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for (int e : outgoing[s]) { d[e] = edges[e].w; pq.push({d[e], e}); }
    while (!pq.empty()) {
        auto [du, e] = pq.top(); pq.pop();
        if (du != d[e]) continue;
        int u = edges[e].v;
        if (u == t) { cout << du << '\n'; return; }
        for (int f : outgoing[u]) {
            ll nd = du + edges[f].w + (edges[e].c == edges[f].c ? 0 : fee[u]);
            if (nd < d[f]) { d[f] = nd; pq.push({nd, f}); }
        }
    }
    cout << -1 << '\n';
}

void partition_oracle() {
    int n, l, r;
    ll c;
    cin >> n >> l >> r >> c;
    vector<ll> h(n + 1), d(n + 1, INF);
    for (int i = 1; i <= n; ++i) cin >> h[i];
    if (n > 5000) {
        ll trips = (n + r - 1) / r;
        if (trips > n / l) { cout << -1 << '\n'; return; }
        if (l == r) {
            ll result = 0;
            for (int start = 1; start <= n; start += l) {
                auto first = h.begin() + start, last = first + l;
                result += c + *max_element(first, last) - *min_element(first, last);
            }
            cout << result << '\n';
            return;
        }
        ll span = *max_element(h.begin() + 1, h.end()) - *min_element(h.begin() + 1, h.end());
        if (span == 0) { cout << trips * c << '\n'; return; }
        if (l == 1 && c == 0) { cout << 0 << '\n'; return; }
        if (l == 1 && r == n && c >= span) { cout << c + span << '\n'; return; }
        bool alternating = true;
        for (int i = 3; i <= n; ++i) alternating &= h[i] == h[i - 2];
        if (alternating && l >= 2) { cout << trips * (c + span) << '\n'; return; }
        bool up = is_sorted(h.begin() + 1, h.end());
        bool down = is_sorted(h.begin() + 1, h.end(), greater<ll>());
        if (up || down) {
            if (!up) for (int i = 1; i <= n; ++i) h[i] = -h[i];
            d[0] = 0;
            multiset<pair<ll, int>> window;
            for (int i = 1; i <= n; ++i) {
                int expired = i - r - 1;
                if (expired >= 0 && d[expired] != INF)
                    window.erase({d[expired] - h[expired + 1], expired});
                int j = i - l;
                if (j >= 0 && d[j] != INF) window.insert({d[j] - h[j + 1], j});
                if (!window.empty()) d[i] = window.begin()->first + h[i] + c;
            }
            cout << (d[n] == INF ? -1 : d[n]) << '\n';
            return;
        }
        if (r > 1500) throw runtime_error("Large case has no independent oracle");
    }
    d[0] = 0;
    for (int i = 1; i <= n; ++i) {
        ll low = INF, high = -INF;
        for (int len = 1; len <= min(i, r); ++len) {
            low = min(low, h[i - len + 1]);
            high = max(high, h[i - len + 1]);
            if (len >= l && d[i - len] != INF)
                d[i] = min(d[i], d[i - len] + c + high - low);
        }
    }
    cout << (d[n] == INF ? -1 : d[n]) << '\n';
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int kind = argc > 1 ? atoi(argv[1]) : 0;
    if (kind == 1) tree_oracle();
    else if (kind == 2) route_oracle();
    else if (kind == 3) partition_oracle();
    else return 1;
}
