#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int LOG = 20;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> a(n + 1), total(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; adj[u].push_back(v); adj[v].push_back(u);
    }
    vector<int> parent(n + 1), depth(n + 1), order{1};
    depth[1] = 1;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u; depth[v] = depth[u] + 1; order.push_back(v);
        }
    }
    vector<array<int, LOG>> jump(n + 1);
    for (int v : order) {
        int p = parent[v];
        if (p && a[p] >= a[v]) {
            for (int j = LOG - 1; j >= 0; --j)
                if (jump[p][j] && a[jump[p][j]] >= a[v]) p = jump[p][j];
            p = jump[p][0];
        }
        jump[v][0] = p;
        for (int j = 1; j < LOG; ++j) jump[v][j] = jump[jump[v][j - 1]][j - 1];
        total[v] = total[p] + a[v] * (depth[v] - depth[p]);
    }
    while (q--) {
        int v, k; cin >> v >> k;
        int left = depth[v] - k + 1, u = v;
        for (int j = LOG - 1; j >= 0; --j)
            if (jump[u][j] && depth[jump[u][j]] >= left) u = jump[u][j];
        cout << total[v] - total[u] + a[u] * (depth[u] - left + 1) << '\n';
    }
}
