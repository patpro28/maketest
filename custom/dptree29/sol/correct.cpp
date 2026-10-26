#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> type(n);
    for (int &t : type) cin >> t;
    struct Edge { int to; ll weight; };
    vector<vector<Edge>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; ll w; cin >> u >> v >> w; --u; --v;
        adj[u].push_back({v,w}); adj[v].push_back({u,w});
    }
    vector<int> parent(n, -1), order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto e : adj[u]) if (e.to != parent[u]) {
            parent[e.to] = u; order.push_back(e.to);
        }
    }
    const ll INF = 1LL << 60;
    vector<array<ll,3>> dp(n);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        dp[u] = {INF,INF,INF};
        dp[u][type[u]] = 0;
        for (auto e : adj[u]) if (parent[e.to] == u) {
            int v = e.to;
            ll best = min({dp[v][0],dp[v][1],dp[v][2]});
            array<ll,3> next{INF,INF,INF};
            for (int a = 0; a < 3; ++a) if (dp[u][a] < INF) {
                next[a] = min(next[a], dp[u][a] + e.weight + best);
                for (int b = 0; b < 3; ++b) if (dp[v][b] < INF) {
                    if (a && b && a != b) continue;
                    int t = max(a,b);
                    next[t] = min(next[t], dp[u][a] + dp[v][b]);
                }
            }
            dp[u] = next;
        }
    }
    cout << min({dp[0][0],dp[0][1],dp[0][2]}) << '\n';
}
