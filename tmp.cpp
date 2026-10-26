#include <bits/stdc++.h>
using namespace std;


const int N = 2e5 + 1;
using cost = array<long long, 3>;
cost dp[N];
int t[N];
void dfs(int u, int p) {
    dp[u] = {inf, inf, inf};
    dp[u][t[u]] = 0;

    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        long long best = min(dp[v]);
        cost nxt = {inf, inf, inf};
        for (int a = 0; a < 3; ++a) {
            nxt[a] = min(nxt[a], dp[u][a] + w + best);
            for (int b = 0; b < 3; ++b) {
                if (a + b == 3) continue;
                int z = max(a, b);
                nxt[z] = min(nxt[z], dp[u][a] + dp[v][b]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, r;
    cin >> n >> r;
    for (int i = 1; i <= n; ++i) {
        cin >> type[i];
        if (type[i] == 0) {
            cin >> C[i][0] >> C[i][1] >> C[i][2];
            isleaf[i] = true;
        } else {
            cin >> L[i] >> R[i];
        }
    }
    dfs(1);
    cout << dp[1][r] << '\n';
}