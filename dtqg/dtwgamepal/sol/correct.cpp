#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n, mod; string s; cin >> m >> n >> mod >> s;
    vector<string> g(m); for (auto &row : g) cin >> row;
    if (m > n) {
        vector<string> h(n, string(m, '#'));
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) h[j][i] = g[i][j];
        g.swap(h); swap(m, n);
    }
    if (g[0][0] == '#' || g[0][0] != g[m-1][n-1]) { cout << 0 << '\n'; return 0; }
    const int K = 1;
    auto id = [=](int x, int y, int q) { return (x * m + y) * K + q; };
    vector<int> dp(m * m * K), next(dp.size());
    dp[id(0, m-1, 0)] = 1 % mod;
    int distance = m + n - 2;
    for (int t = 0; t < distance / 2; ++t) {
        fill(next.begin(), next.end(), 0);
        for (int x = max(0, t-n+1); x <= min(m-1, t); ++x) {
            int y = t - x;
            for (int u = max(x, distance-t-n+1); u < m; ++u) {
                int v = distance - t - u;
                if (v < y || v >= n) continue;
                for (int q = 0; q < K; ++q) if (int ways = dp[id(x,u,q)]) {
                    for (int down = 0; down < 2; ++down) for (int up = 0; up < 2; ++up) {
                        int nx = x + down, ny = y + 1 - down;
                        int nu = u - up, nv = v - 1 + up;
                        if (nx >= m || ny >= n || nu < nx || nv < ny) continue;
                        char c = g[nx][ny];
                        if (c == '#' || c != g[nu][nv]) continue;
                        int nq = 0;
                        int &value = next[id(nx,nu,nq)];
                        value += ways; if (value >= mod) value -= mod;
                    }
                }
            }
        }
        dp.swap(next);
    }
    int answer = 0, t = distance / 2;
    for (int x = 0; x < m; ++x) for (int u = x; u < m; ++u) {
        int y = t - x, v = distance - t - u;
        if (y < 0 || y >= n || v < y || v >= n) continue;
        if ((u-x) + (v-y) != distance % 2) continue;
        answer += dp[id(x,u,0)]; if (answer >= mod) answer -= mod;
    }
    cout << answer << '\n';
}
