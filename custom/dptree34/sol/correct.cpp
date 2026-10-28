#include <algorithm>
#include "fast_io.h"
#include <vector>
using namespace std;
using ll = long long;

int main() {
    FastInput input;
    int n;
    input.read(n);
    vector<ll> value(n);
    for (ll &a : value) input.read(a);
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u,v;
        input.read(u); input.read(v);
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Every parent comes before its children in order.
    vector<int> parent(n,-1),order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u;
            order.push_back(v);
        }
    }
    vector<ll> dp(n);
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        ll best = -(1LL << 60);
        bool has_child = false;
        for (int v : adj[u]) if (parent[v] == u) {
            has_child = true;
            best = max(best,dp[v]);
        }
        dp[u] = value[u];
        if (has_child) dp[u] += best; // A journey must reach a leaf.
    }
    writeValue(dp[0]);
}
