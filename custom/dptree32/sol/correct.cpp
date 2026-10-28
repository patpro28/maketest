#include <algorithm>
#include "fast_io.h"
#include <vector>
using namespace std;
using ll = long long;

int main() {
    FastInput input;
    int n;
    input.read(n);
    vector<ll> dp(n);
    for (ll &a : dp) input.read(a);
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
    // Reversing order makes every child ready before its parent.
    for (int i = n-1; i > 0; --i) {
        int u = order[i];
        dp[parent[u]] += dp[u];
    }
    writeArray(dp);
}
