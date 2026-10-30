#include <array>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    vector<long long> p(n + 1), s(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x; if (scanf("%d", &x) != 1) return 0;
        p[i] = p[i-1]; s[i] = s[i-1];
        if (x > 0) p[i] += x; else if (x < 0) s[i] += x;
    }
    while (q--) {
        int l, r; if (scanf("%d%d", &l, &r) != 2) return 0;
        printf("%lld %lld\n", p[r]-p[l-1], s[r]-s[l-1]);
    }
}
