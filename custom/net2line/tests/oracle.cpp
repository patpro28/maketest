#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>
struct Edge { int a, b, w; };
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        if (n > 5) return 1;
        std::vector<Edge> edges;
        for (int row = 0; row < 2; ++row) for (int i = 0; i < n-1; ++i) {
            int x; scanf("%d", &x); edges.push_back({row*n+i, row*n+i+1, x});
        }
        for (int i = 0; i < n; ++i) {
            int x; scanf("%d", &x); edges.push_back({i, n+i, x});
        }
        int best = 1000000000;
        for (int mask = 0; mask < (1 << edges.size()); ++mask) {
            int p[10]; std::iota(p, p+2*n, 0);
            auto root = [&](int x) { while (p[x] != x) x = p[x]; return x; };
            int cost = 0, components = 2*n;
            for (int i = 0; i < int(edges.size()); ++i) if ((mask >> i) & 1) {
                cost += edges[i].w;
                int a = root(edges[i].a), b = root(edges[i].b);
                if (a != b) { p[a] = b; --components; }
            }
            if (components == 1 && cost % 2 == 0) best = std::min(best, cost);
        }
        printf("%d\n", best == 1000000000 ? -1 : best);
    }
}
