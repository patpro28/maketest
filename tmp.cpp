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

int cnt[200], a[200];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q; cin >> n >> q;

    // Chuẩn bị trước
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[i] = cnt[i - 1] + (a[i] > 0);
    }

    // Vào phòng thi
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << cnt[r] - cnt[l - 1] << '\n';
    }
}