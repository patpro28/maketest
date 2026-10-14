#include <algorithm>
#include <cstdio>
#include <vector>

struct DSU {
    int p[4] = {0, 1, 2, 3};
    int root(int x) { return p[x] == x ? x : p[x] = root(p[x]); }
    void join(int x, int y) { p[root(x)] = root(y); }
};

int main() {
    if (fopen("net.inp", "r")) freopen("net.inp", "r", stdin), freopen("net.out", "w", stdout);
    // Old frontier: 0,1. New frontier: 2,3.
    int next[2][8];
    for (int s = 0; s < 2; ++s) for (int mask = 0; mask < 8; ++mask) {
        DSU d;
        if (s) d.join(0, 1);
        if (mask & 1) d.join(0, 2);
        if (mask & 2) d.join(1, 3);
        if (mask & 4) d.join(2, 3);
        bool valid = true;
        for (int x = 0; x < 2; ++x)
            if (d.root(x) != d.root(2) && d.root(x) != d.root(3)) valid = false;
        next[s][mask] = valid ? int(d.root(2) == d.root(3)) : -1;
    }
    int t;
    if (scanf("%d", &t) != 1) return 0;
    const long long INF = 1LL << 60;
    while (t--) {
        int n;
        scanf("%d", &n);
        std::vector<int> u(n - 1), v(n - 1);
        for (int &x : u) scanf("%d", &x);
        for (int &x : v) scanf("%d", &x);
        int w;
        scanf("%d", &w);
        long long dp[2][2] = {{0, INF}, {INF, INF}};
        dp[1][w & 1] = w;
        for (int i = 1; i < n; ++i) {
            scanf("%d", &w);
            long long ndp[2][2] = {{INF, INF}, {INF, INF}};
            for (int mask = 0; mask < 8; ++mask) {
                int cost = ((mask & 1) ? u[i-1] : 0)
                         + ((mask & 2) ? v[i-1] : 0) + ((mask & 4) ? w : 0);
                for (int s = 0; s < 2; ++s) if (next[s][mask] >= 0)
                    for (int parity = 0; parity < 2; ++parity) {
                        auto &dest = ndp[next[s][mask]][parity ^ (cost & 1)];
                        dest = std::min(dest, dp[s][parity] + cost);
                    }
            }
            for (int s = 0; s < 2; ++s) for (int b = 0; b < 2; ++b) dp[s][b] = ndp[s][b];
        }
        printf("%lld\n", dp[1][0] == INF ? -1LL : dp[1][0]);
    }
}
