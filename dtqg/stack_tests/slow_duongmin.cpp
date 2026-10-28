// Correct small-data solver intentionally using pop + rollback on DFS paths.
// Its work is quadratic on a long increasing stem with many low-valued leaves.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
struct Event { int u, parent, leave, snapshot; };
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> a(n + 1), total(n + 1), answer(q);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) { int u, v; cin >> u >> v; adj[u].push_back(v); adj[v].push_back(u); }
    vector<vector<pair<int, int>>> queries(n + 1);
    for (int i = 0; i < q; ++i) { int v, k; cin >> v >> k; queries[v].push_back({k, i}); }
    vector<int> depth(n + 1), stack, history;
    vector<Event> todo{{1, 0, 0, 0}};
    while (!todo.empty()) {
        auto e = todo.back(); todo.pop_back();
        int u = e.u;
        if (e.leave) {
            stack.pop_back();
            while (int(history.size()) > e.snapshot) { stack.push_back(history.back()); history.pop_back(); }
            continue;
        }
        depth[u] = depth[e.parent] + 1;
        int snapshot = int(history.size());
        while (!stack.empty() && a[stack.back()] >= a[u]) { history.push_back(stack.back()); stack.pop_back(); }
        int p = stack.empty() ? 0 : stack.back();
        total[u] = total[p] + a[u] * (depth[u] - depth[p]);
        stack.push_back(u);
        for (auto [k, id] : queries[u]) {
            int left = depth[u] - k + 1;
            auto it = lower_bound(stack.begin(), stack.end(), left, [&](int x, int d) { return depth[x] < d; });
            int w = *it;
            answer[id] = total[u] - total[w] + a[w] * (depth[w] - left + 1);
        }
        todo.push_back({u, e.parent, 1, snapshot});
        for (int v : adj[u]) if (v != e.parent) todo.push_back({v, u, 0, 0});
    }
    for (ll value : answer) cout << value << '\n';
}
