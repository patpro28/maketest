// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
using namespace std;
using ll = long long int;
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<pair<int, char>>> adj(n, vector<pair<int, char>>());
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u ,--v;
            char c; cin >> c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }
        string s; cin >> s;
        int m = s.size();
        vector<vector<int>> up(n, vector<int>(m+1, 0));
        vector<vector<int>> down(n, vector<int>(m+1, 0));

        // up[i][j] -> longest subsequence from the subtree of u going up, considering the first i chars of s
        // down[i][j] -> longest subseq in subtree of u going down, considering last i chars of s

        int ans = 0;
        auto dfs = [&] (const auto &self, int u, int p) -> void {
            for (auto [v, c] : adj[u]) {
                if (v == p) continue;
                self(self, v, u);
                for (int i = 1; i <= m; ++i) {
                    int cur = up[v][i];
                    if (c == s[i-1]) cur = max(cur, up[v][i-1] + 1);
                    ans = max(ans, cur + down[u][m-i]);

                    cur = down[v][i];
                    if (c == s[m-i]) cur = max(cur, down[v][i-1] + 1);
                    ans = max(ans, cur + up[u][m-i]);
                }
                for (int i = 1; i <= m; ++i) {
                    int cur = up[v][i];
                    if (c == s[i-1]) cur = max(cur, up[v][i-1] + 1);
                    up[u][i] = max(up[u][i], cur);

                    cur = down[v][i];
                    if (c == s[m-i]) cur = max(cur, down[v][i-1] + 1);
                    down[u][i] = max(down[u][i], cur);
                }

                for (int i = 1; i <= m; ++i) up[u][i] = max(up[u][i], up[u][i-1]), down[u][i] = max(down[u][i], down[u][i-1]);
            }
        };
        dfs(dfs, 0, 0);
        cout << ans << '\n';
    }
}